import _io
import AdventOfCode.helper as h

is_test = False

if not is_test:
    input_file = open(h.get_input_file())
else:
    input_file = ['forward 5','down 5','forward 8','up 3','down 8','forward 2']


h_pos = 0
v_pos = 0
for instruction in input_file:
    direction = instruction.split(' ')[0]
    amount = int(instruction.split(' ')[1])

    if direction == 'forward':
        h_pos += amount
    elif direction == 'up':
        v_pos -= amount
    elif direction == 'down':
        v_pos += amount

if isinstance(input_file, _io.TextIOWrapper):
    input_file.close()

print('Part One')
print(f'horizontal position: {h_pos}. vertical position = {v_pos}. result: {h_pos * v_pos}')


## start part 2

if not is_test:
    input_file = open(h.get_input_file())
else:
    input_file = ['forward 5','down 5','forward 8','up 3','down 8','forward 2']


h_pos = 0
v_pos = 0
aim = 0
for instruction in input_file:
    direction = instruction.split(' ')[0]
    amount = int(instruction.split(' ')[1])

    if direction == 'forward':
        h_pos += amount
        v_pos += aim * amount
    elif direction == 'down':
        aim += amount
    elif direction == 'up':
        aim -= amount

if isinstance(input_file, _io.TextIOWrapper):
    input_file.close()

print('Part Two')
print(f'horizontal position: {h_pos}. vertical position: {v_pos}. aim: {aim}. result: {v_pos * h_pos}')
