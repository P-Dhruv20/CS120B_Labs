#inverted inputs
tests = [ {'description': 'PINA: 0xFF => PORTC: 0x40',
    'steps': [ {'inputs': [('PINA',0xFF)], 'iterations': 5 } ],
    'expected': [('PORTC',0x40)],
    },
	{'description': 'PINA: 0xFE => PORTC: 0x60',
    'steps': [ {'inputs': [('PINA',0x01)], 'iterations': 5 } ],
    'expected': [('PORTC',0x60)],
    },
	{'description': 'PINA: 0xFB => PORTC: 0x70',
    'steps': [ {'inputs': [('PINA',0x04)], 'iterations': 5 } ],
    'expected': [('PORTC',0x70)],
    },
	{'description': 'PINA: 0xF7 => PORTC: 0x3C',
    'steps': [ {'inputs': [('PINA',0x08)], 'iterations': 5 } ],
    'expected': [('PORTC',0x3C)],
    },
	{'description': 'PINA: 0xF0 => PORTC: 0x3F',
    'steps': [ {'inputs': [('PINA',0x0F)], 'iterations': 5 } ],
    'expected': [('PORTC',0x3F)],
    },
]