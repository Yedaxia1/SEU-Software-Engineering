import math

def get_functions():
    return [_nature, _log, _augmented, _boolean]

def _nature(term, term_dict):
    return term_dict['tf'][term]

def _log(term, term_dict):
    tf = term_dict['tf'][term]
    return 1 + math.log10(1 + tf) if tf > 0 else 0

def _augmented(term, term_dict):
    tf = float(term_dict['tf'][term])
    max_tf = float(term_dict['max_freq']['freq'])
    return 0.5 + (0.5 * tf) / max_tf

def _boolean(term, term_dict):
    tf = term_dict['tf'][term]
    return 1 if tf > 0 else 0