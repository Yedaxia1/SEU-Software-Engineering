import math

def get_functions():
    return [_none, _idf, _prob_idf]

def _none(N, df):
    return 1

def _idf(N, df):
    return math.log10(float(N) / float(df))

def _prob_idf(N, df):
    v = math.log10(float(N - df) / float(df))
    return max(0.0, v)