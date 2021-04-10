tests = [ {'description': 'PINA: 0x00, PINB: 0x37, PINC: 0x55 => PORTD: 0x22',
    'steps': [ {'inputs': [('PINA',0x00), ('PINB', 0x37), ('PINC',0x55)], 'iterations': 5 } ],
    'expected': [('PORTD',0x23)],
    },
	{'description': 'PINA: 64, PINB: 64, PINC: 64 => PORTD: 0x31',
    'steps': [ {'inputs': [('PINA',0x40), ('PINB', 0x40), ('PINC',0x40)], 'iterations': 5 } ],
    'expected': [('PORTD',0x31)],
    },
	{'description': 'PINA: 0, PINB: 35, PINC: 85 => PORTD: 0x1E',
    'steps': [ {'inputs': [('PINA',0x00), ('PINB', 0x23), ('PINC',0x55)], 'iterations': 5 } ],
    'expected': [('PORTD',0x1E)],
    },
    ]
#watch = ['PORTD']
