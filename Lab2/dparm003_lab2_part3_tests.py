tests = [ {'description': 'PINA: 0x00 => PORTC: 0x04',
    'steps': [ {'inputs': [('PINA',0x00)], 'iterations': 5 } ],
    'expected': [('PORTC',0x04)],
    },
	{'description': 'PINA: 0x01 => PORTC: 0x03',
    'steps': [ {'inputs': [('PINA',0x01)], 'iterations': 5 } ],
    'expected': [('PORTC',0x03)],
    },
	{'description': 'PINA: 0x02 => PORTC: 0x03',
    'steps': [ {'inputs': [('PINA',0x02)], 'iterations': 5 } ],
    'expected': [('PORTC',0x03)],
    },
	{'description': 'PINA: 0x03 => PORTC: 0x02',
    'steps': [ {'inputs': [('PINA',0x03)], 'iterations': 5 } ],
    'expected': [('PORTC',0x02)],
    },
	{'description': 'PINA: 0x04 => PORTC: 0x03',
    'steps': [ {'inputs': [('PINA',0x04)], 'iterations': 5 } ],
    'expected': [('PORTC',0x03)],
    },
	{'description': 'PINA: 0x05 => PORTC: 0x02',
    's0teps': [ {'inputs': [('PINA',0x05)], 'iterations': 5 } ],
    'expected': [('PORTC',0x02)],
    },
	{'description': 'PINA: 0x06 => PORTC: 0x02',
    'steps': [ {'inputs': [('PINA',0x06)], 'iterations': 5 } ],
    'expected': [('PORTC',0x02)],
    },
	{'description': 'PINA: 0x07 => PORTC: 0x01',
    'steps': [ {'inputs': [('PINA',0x07)], 'iterations': 5 } ],
    'expected': [('PORTC',0x01)],
    },
	{'description': 'PINA: 0x08 => PORTC: 0x03',
    'steps': [ {'inputs': [('PINA',0x08)], 'iterations': 5 } ],
    'expected': [('PORTC',0x03)],
    },
	{'description': 'PINA: 0x09 => PORTC: 0x02',
    'steps': [ {'inputs': [('PINA',0x09)], 'iterations': 5 } ],
    'expected': [('PORTC',0x02)],
    },
	{'description': 'PINA: 0x0A => PORTC: 0x02',
    'steps': [ {'inputs': [('PINA',0x0A)], 'iterations': 5 } ],
    'expected': [('PORTC',0x02)],
    },
	{'description': 'PINA: 0x0B => PORTC: 0x01',
    'steps': [ {'inputs': [('PINA',0x0B)], 'iterations': 5 } ],
    'expected': [('PORTC',0x01)],
    },
	{'description': 'PINA: 0x0C => PORTC: 0x02',
    'steps': [ {'inputs': [('PINA',0x0C)], 'iterations': 5 } ],
    'expected': [('PORTC',0x02)],
    },
	{'description': 'PINA: 0x0D => PORTC: 0x01',
    'steps': [ {'inputs': [('PINA',0x0D)], 'iterations': 5 } ],
    'expected': [('PORTC',0x01)],
    },
	{'description': 'PINA: 0x0E => PORTC: 0x01',
    'steps': [ {'inputs': [('PINA',0x0E)], 'iterations': 5 } ],
    'expected': [('PORTC',0x01)],
    },
	{'description': 'PINA: 0x0F => PORTC: 0x80',
    'steps': [ {'inputs': [('PINA',0x0F)], 'iterations': 5 } ],
    'expected': [('PORTC',0x80)],
    },
    ]
#watch = ['PORTC']