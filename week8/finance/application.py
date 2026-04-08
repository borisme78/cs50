import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True


# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    rows = db.execute(
        """
        SELECT symbol, SUM(shares) as total_shares
        FROM transactions
        WHERE user_id = ?
        GROUP BY symbol
        HAVING SUM(shares) > 0
""",
        session["user_id"],
    )

    stocks = []  # список для збереження інформацій про акції
    total_assets = 0  # загальна вартість усіх акцій

    # проходимо по кожній акції
    for row in rows:
        symbol = row["symbol"]  # акція
        shares = row["total_shares"]  # кількість акцій

        # актуальна ціна акції
        quote = lookup(symbol.upper())
        if quote:
            price = quote["price"]

            # загальна вартість акції
            total = shares * price

            # додаєм до загального балансу акцій

            total_assets += total

            # додаєм дані у список html
            stocks.append(
                {"symbol": symbol, "shares": shares, "price": price, "total": total}
            )
        else:
            continue

    # отримуєм грошовий баланс користувача
    cash_row = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
    cash = cash_row[0]["cash"]

    # рахуєм загальний (акції + кеш)
    grand_total = cash + total_assets

    # передаємо все в шаблон html
    return render_template(
        "index.html",
        stocks=stocks,  # список акцій
        cash=cash,  # гроші
        total=grand_total,  # загальний баланс
    )


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        if not symbol or not shares:
            return apology("must provide symbol and shares", 400)

        if not shares.isdigit() or int(shares) <= 0:
            return apology("shares must be a positive integer", 400)

        stock = lookup(symbol.upper())

        if not stock:
            return apology("invalid symbol", 400)

        user_id = session.get("user_id")
        rows = db.execute("SELECT cash FROM users WHERE id = ?", user_id)
        cash = rows[0]["cash"]
        total_cost = stock["price"] * int(shares)
        if cash < total_cost:
            return apology("not enough cash", 400)

        db.execute(
            " UPDATE users SET cash = cash - ? WHERE id = ?", total_cost, user_id
        )

        db.execute(
            """
            INSERT INTO transactions (user_id, symbol, shares, price) 
            VALUES (?, ?, ?, ?)
        """,
            user_id,
            stock["symbol"],
            int(shares),
            stock["price"],
        )
        return redirect("/")
    return render_template("buy.html")


@app.route("/check", methods=["GET"])
def check():
    """Return true if username available, else false, in JSON format"""
    user_name = request.form.get(user_name)


    if not user_name or user_name < 1:
        return jsonify(False)
    
    rows = db.execute(
    """
    SELECT * FROM users WHERE id = &
    """,
    user_name
    )

    if len(row) == 0:
        return jsonify(True)
    else:
        return jsonify(False)


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    transactions = db.execute("""
    SELECT symbol, shares, price, transacted FROM transactions WHERE user_id = ? ORDER BY transacted DESC
    """,
    session["user_id"])
    return render_template("history.html", transactions = transactions)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = :username",
            username=request.form.get("username"),
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "GET":
        return render_template("quote.html")
    else:
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("must provide symbol", 400)
        quote = lookup(symbol.upper())
        if not quote:
            return apology("invalid symbol", 400)
    return render_template("quoted.html", quote=quote)


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":

        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        if not username:
            return apology("must provide username", 400)
        elif not password:
            return apology("must provide password", 400)
        elif not confirmation:
            return apology("must provide password (again)", 400)
        elif password != confirmation:
            return apology("passwords do not match", 400)

        generate_password_hash(password)

        try:
            db.execute(
                "INSERT INTO users (username, hash) VALUES (:username, :hash)",
                username=username,
                hash=generate_password_hash(password),
            )
        except:
            return apology("username already exists", 400)

        rows = db.execute("SELECT id FROM users WHERE username = ?", username)
        session["user_id"] = rows[0]["id"]
        return redirect("/")

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")
        symbol = symbol.upper()
        user = session["user_id"]

        if not symbol or not shares:
            return apology("must provide symbol and shares", 400)

        if not shares or int(shares) <= 0:
            return apology("shares must be a positive integer", 400)

        shares = int(shares)

        rows = db.execute(
            """SELECT SUM (shares) 
            AS total_shares
            FROM transactions
            WHERE user_id = ?
            AND symbol = ?
            GROUP BY symbol""",
            user,
            symbol,
        )
        if not rows:
            return apology("You don't own this stock", 400)

        user_shares = rows[0]["total_shares"]

        if user_shares < shares:
            return apology("Not enough shares to sell", 400)

        stock_data = lookup(symbol)

        price = stock_data["price"]

        total_sale_value = price * shares

        db.execute(
            """
        UPDATE users 
        SET cash = cash + ?
        WHERE id = ? 
        """,
            total_sale_value,
            user,
        )
        db.execute(
            "INSERT INTO transactions (user_id, symbol, shares, price) VALUES (?, ?, ?, ?)",
            user,
            symbol,
            -shares,
            price,
        )

        return redirect("/")
    # GET METHOD
    else:
        rows = db.execute(
            """
            SELECT symbol, SUM(shares) AS total_shares
            FROM transactions
            WHERE user_id = ?
            GROUP BY symbol
            HAVING SUM(shares) > 0
            """,
            session["user_id"],
        )
        return render_template("sell.html", symbol=rows)


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
