import _io
import AdventOfCode.helper as h



input_file = h.get_input_file()

test_file = ['00100','11110','10110','10111','10101','01111','00111','11100','10000','11001','00010','01010']

is_test = 0


if is_test:
    instructions = test_file
    CODE_LENGTH = 5
else:
    instructions = h.file_to_list((input_file))
    CODE_LENGTH = 12


## we can solve this by knowing that each input value is 12 characters long
## we can keep a counter for each column. when the column value is 1, we increment the counter
## at the end can compare each column total to the total number of lines in the file
## thereby getting the most common bit for each column

column_totals = [0 for i in range(CODE_LENGTH)]
num_codes = 0
for code in instructions:
    for i in range(CODE_LENGTH):
        column_totals[i] += int(code[i:i+1])

    num_codes += 1

print(f"column totals: {column_totals}")
##now that we have the sums of each column, we need compare to the total lines
gamma_code_binary = [0 for i in range(CODE_LENGTH)]
epsilon_code_binary = [0 for i in range(CODE_LENGTH)]
for i in range(len(column_totals)):
    if column_totals[i] >= num_codes/2:
        gamma_code_binary[i] = 1
        epsilon_code_binary[i] = 0
    else:
        gamma_code_binary[i] = 0
        epsilon_code_binary[i] = 1


gamma_code_binary = ''.join(map(str, gamma_code_binary))
gamma_code_decimal = int(gamma_code_binary, 2)

epsilon_code_binary = ''.join(map(str, epsilon_code_binary))
epsilon_code_decimal = int(epsilon_code_binary, 2)


print("-----Part One-----")
print(f"gamma code: {gamma_code_decimal}. binary: {gamma_code_binary}")
print(f"epsilon code: {epsilon_code_decimal}. binary: {epsilon_code_binary}")
print(f"power consumption: {gamma_code_decimal * epsilon_code_decimal}")
print()
print()

## start part 2
def most_common_bit(list_of_codes, bit_position):
    ## use the same logic here as is used above to get the column totals
    ## but only look at position <bit_position>
    col_total = 0
    for code in list_of_codes:
        col_total += int(code[bit_position])

    if col_total >= len(list_of_codes)/2:
        return 1
    else:
        return 0


##originally tried to do this as just the reverse of most_common_bit
## but that did not work for part 2
def least_common_bit(list_of_codes, bit_position):
    col_total = 0
    for code in list_of_codes:
        col_total += int(code[bit_position])

    if col_total >= len(list_of_codes)/2:
        return 0
    else:
        return 1


def filter_codes(list_of_codes, bit_position, filter_bit):
    ##return a subset of <list_of_codes> which have in their <bit_position>
    ## the <filter_bit>

    ##have to cast <i[bit_position]> to int because <filter_bit> is an integer
    return [i for i in list_of_codes if int(i[bit_position]) == filter_bit]


o2_rating_bin, co2_rating_bin = 0, 0
possible_o2_codes = instructions
possible_co2_codes = possible_o2_codes
bit_pos = 0


while bit_pos < CODE_LENGTH:
    mcb = most_common_bit(possible_o2_codes, bit_pos)
    lcb = least_common_bit(possible_co2_codes, bit_pos)

    if (len(possible_o2_codes) > 1):
        possible_o2_codes = filter_codes(possible_o2_codes, bit_pos, mcb)

    if (len(possible_co2_codes) > 1):
        possible_co2_codes = filter_codes(possible_co2_codes, bit_pos, lcb)

    bit_pos += 1


o2_rating_bin = ''.join(map(str, possible_o2_codes))
co2_rating_bin = ''.join(map(str, possible_co2_codes))

o2_rating_dec = int(o2_rating_bin, 2)
co2_rating_dec = int(co2_rating_bin, 2)






print("-----Part Two-----")
print(f"O2 Generator Rating: {o2_rating_dec}")
print(f"CO2 Generator Rating: {co2_rating_dec}")
print(f"Life Support Rating: {o2_rating_dec * co2_rating_dec}")

