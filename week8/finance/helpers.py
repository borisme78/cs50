import requests
import urllib.parse

from flask import redirect, render_template, request, session
from functools import wraps

import finnhub


def apology(message, code=400):
    """Render message as an apology to user."""
    def escape(s):
        """
        Escape special characters.

        https://github.com/jacebrowning/memegen#special-characters
        """
        for old, new in [("-", "--"), (" ", "-"), ("_", "__"), ("?", "~q"),
                         ("%", "~p"), ("#", "~h"), ("/", "~s"), ("\"", "''")]:
            s = s.replace(old, new)
        return s
    return render_template("apology.html", top=code, bottom=escape(message)), code


def login_required(f):
    """
    Decorate routes to require login.

    http://flask.pocoo.org/docs/1.0/patterns/viewdecorators/
    """
    @wraps(f)
    def decorated_function(*args, **kwargs):
        if session.get("user_id") is None:
            return redirect("/login")
        return f(*args, **kwargs)
    return decorated_function


def lookup(symbol):
    """Look up quote for symbol using Finnhub API."""
    API_KEY = "d739dp1r01qjjol27e10d739dp1r01qjjol27e1g"  # зареєструйся на finnhub.io і встав API key
    finnhub_client = finnhub.Client(api_key=API_KEY)

    # url = f"https://finnhub.io/api/v1/quote?symbol={symbol}&token={API_KEY}"
    headers = {"X-Finnhub-Token": API_KEY}
    url = f"https://finnhub.io/api/v1/quote?symbol={symbol}"
    try:
        # response = requests.get(url)
        response = requests.get(url, headers=headers)
        response.raise_for_status()
        data = response.json()
        if data.get("c") == 0 or data.get("c") is None:
            return None
        
        return {
            "name": symbol,          # Finnhub не повертає повну назву компанії
            "price": float(data["c"]),
            "symbol": symbol
        }
    except (requests.RequestException, KeyError, TypeError, ValueError):
        return None


def usd(value):
    """Format value as USD."""
    return f"${value:,.2f}"
