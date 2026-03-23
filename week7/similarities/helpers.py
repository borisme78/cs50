from nltk.tokenize import sent_tokenize

def lines(a, b):
    """Return lines in both a and b"""

    result = []

    A = a.split("\n")
    B = b.split("\n")

    for line in A:
        if line in B and line not in result:
            result.append(line)

    return result


def sentences(a, b):
    """Return sentences in both a and b"""
    result = []

    sentences_A = sent_tokenize(a)
    sentences_B = sent_tokenize(b)

    for sentence in sentences_A:
        if sentence in sentences_B and sentence not in result:
            result.append(sentence)


    return result


def substrings(a, b, n):
    """Return substrings of length n in both a and b"""

    result = []
    
    sub_a = []

    for i in range(len(a) - n + 1):
        subsring = a[i : i + n]
        sub_a.append(subsring)
    
    for i in range(len(b) - n + 1):
        subsring = b[i : i + n]
        if subsring in sub_a and subsring not in result:
            result.append(subsring)

    return result
