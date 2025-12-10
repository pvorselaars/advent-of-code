#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <limits.h>
#include "../../tester.h"

#define MAX_LIGHTS 64
#define MAX_COUNTERS 64
#define MAX_BUTTONS 64
#define MAX_LINE 1024

typedef struct {
	int n_lights;
	int n_buttons;
	int n_counters;
	bool lights[MAX_LIGHTS];
	bool effects[MAX_BUTTONS][MAX_LIGHTS];
	unsigned counters[MAX_COUNTERS];
} machine;

void parse_lights(char *line, machine *m)
{
	int start = 0, end = 0;
	int len = strlen(line);

	for (int i = 0; i < len; i++) {
		if (line[i] == '[')
			start = i + 1;
		if (line[i] == ']') {
			end = i;
			break;
		}
	}

	m->n_lights = end - start;
	for (int i = 0; i < m->n_lights; i++) {
		m->lights[i] = (line[start + i] == '#');
	}
}

void parse_buttons(char *line, machine *m)
{
	m->n_buttons = 0;
	int len = strlen(line);

	for (int i = 0; i < MAX_BUTTONS; i++) {
		for (int j = 0; j < MAX_LIGHTS; j++) {
			m->effects[i][j] = false;
		}
	}

	for (int i = 0; i < len; i++) {
		if (line[i] == '(') {
			i++;
			while (i < len && line[i] != ')') {
				if (line[i] >= '0' && line[i] <= '9') {
					int light_index = 0;
					while (i < len && line[i] >= '0' && line[i] <= '9') {
						light_index = light_index * 10 + (line[i] - '0');
						i++;
					}
					if (light_index < m->n_lights) {
						m->effects[m->n_buttons][light_index] = true;
					}
				} else {
					i++;
				}
			}
			m->n_buttons++;
		}
	}

}

void parse_joltage(char *line, machine *m)
{
	m->n_counters = 0;
	int len = strlen(line);

	for (int i = 0; i < len; i++) {
		if (line[i] == '{') {
			i++;
			while (i < len && line[i] != '}') {
				if (line[i] >= '0' && line[i] <= '9') {
					int joltage = 0;
					while (i < len && line[i] >= '0' && line[i] <= '9') {
						joltage = joltage * 10 + (line[i] - '0');
						i++;
					}
					m->counters[m->n_counters] = joltage;
					m->n_counters++;
				} else {
					i++;
				}
			}
			break;
		}
	}

}

void parse_machine(char *line, machine *m)
{
	parse_lights(line, m);
	parse_buttons(line, m);
	parse_joltage(line, m);
}

int solve_machine_lights(machine* m) {
    int min_presses = INT_MAX;
    
    for (int mask = 1; mask < (1 << m->n_buttons); mask++) {
        
        bool result_lights[MAX_LIGHTS] = {false};
        
        for (int button = 0; button < m->n_buttons; button++) {
            if (mask & (1 << button)) {
                for (int light = 0; light < m->n_lights; light++) {
                    if (m->effects[button][light]) {
                        result_lights[light] = !result_lights[light];
                    }
                }
            }
        }
        
        bool valid = true;
        for (int light = 0; light < m->n_lights; light++) {
            if (result_lights[light] != m->lights[light]) {
                valid = false;
                break;
            }
        }
        
        if (valid) {
            int presses = __builtin_popcount(mask);
            if (presses < min_presses) {
                min_presses = presses;
            }
        }
    }
    
    return min_presses;
}

uint64_t solution1(const char *filename)
{
	FILE *input = fopen(filename, "r");
	if (!input)
		return -1;

	char line[MAX_LINE];

	uint64_t sum = 0;

	while (fgets(line, sizeof(line), input)) {
		machine m;
		parse_machine(line, &m);
		sum += solve_machine_lights(&m);
	}

	return sum;
}

int main(int argc, char *argv[])
{
	test("solution 1, sample", solution1("sample"), 7);
	test("solution 1, input", solution1("input"), 475);
}
