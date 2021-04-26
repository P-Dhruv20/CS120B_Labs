#inverted inputs
tests = [ {'description': 'PINA: 0xFE, 0xFF, 0xFE => PORTB: 0x01',
    'steps': [{'inputs': [('PINA', 0xFE)], 'iterations': 5},
        {'inputs': [('PINA', 0xFF)], 'iterations': 5},
        {'inputs': [('PINA', 0xFE)], 'iterations': 5}],
    'expected': [('PORTB',0x01)],
    },
    ]
#watch = ['state']

