tests = [ {'description': 'PINA: 0x00, PINB: 0x37, PINC: 0x55 => PORTD: 0x22',
    'steps': [ {'inputs': [('PINA',0x00), ('PINB', 0x37), ('PINC',0x55)], 'iterations': 5 } ],
    'expected': [('PORTD',0x22)],
    },
    ]
#watch = ['PORTD']
