# Run your copy of the boot code.
# Immediately before any instruction is executed a second time, what value is in the accumulator?

# don't assume each instruction is unique
# we could read each line into a list
# then look at each list item in turn, keeping track of which index value we move to each time
# if we have a duplicate index value, we can stop and look at the accumulator


boot_code_file = '/home/smoint/Documents/PythonStuff/AdventOfCode/InputFiles/day_eight_input'
# boot_code_file = '/home/smoint/thingus'

accumulator = 0
idx = 0
executed_instructions = []
num_instructions = 0

boot_code = [line for line in open(boot_code_file)]
while idx not in executed_instructions:
    executed_instructions.append(idx)
    instruction = boot_code[idx]
    num_instructions += 1
    # print(f'step:{num_instructions}. index:{idx}. instruction: {instruction[:3]}. value: {int(instruction[3:])}')
    if instruction[:3] == 'acc':
        accumulator += int(instruction[3:])
        idx += 1
    elif instruction[:3] == 'jmp':
        idx += int(instruction[3:])
    elif instruction[:3] == 'nop':
        idx += 1
print("Accumulator value:", accumulator)
# ---END PART ONE--- #



# ---START PART TWO--- #
# brute force method

jorn_indexes = [] # jorn stands for jump or nop
idx = 0
for line in boot_code:
    if line[:3] != 'acc':
        jorn_indexes.append(idx)
    idx += 1

for jorn in jorn_indexes:
    executed_instructions = []
    # print(boot_code[jorn])
    altered_boot_code = boot_code.copy()
    # print(altered_boot_code)
    if boot_code[jorn][:3] == 'jmp':
        altered_boot_code[jorn] = 'nop' + boot_code[jorn][3:]
    else:
        altered_boot_code[jorn] = 'jmp' + boot_code[jorn][3:]
    # print(altered_boot_code)
    # print(len(altered_boot_code))
    idx = 0
    accumulator = 0
    while idx < len(altered_boot_code):
        if idx in executed_instructions:
            break

        executed_instructions.append(idx)
        instruction = altered_boot_code[idx]
        if instruction[:3] == 'acc':
            accumulator += int(instruction[3:])
            idx += 1
        elif instruction[:3] == 'jmp':
            idx += int(instruction[3:])
        elif instruction[:3] == 'nop':
            idx += 1
        # print('index:', idx, '. Accumulator:', accumulator)

    if idx >= len(altered_boot_code):
        break

# print(altered_boot_code)
print(jorn)
print("Adjusted Accumulator value:", accumulator)
for o, a in (zip(boot_code, altered_boot_code)):
    if o != a:
        print(f"original:{o}. altered:{a}")

