
INPUT_FILE = '/home/wrowsers/PythonStuff/AdventOfCode/2020/Inputs/day_nine'
THINGUS_FILE = '/home/wrowsers/thingus'





class XMASCipher:
    def __init__(self, cipher_file):
        self.cipher_file = cipher_file
        self.cipher = self._extract_cipher()
        self.PREAMBLE_LENGTH = 25

    def _extract_cipher(self):
        with open(self.cipher_file) as cf:
            rtn = [int(line) for line in cf]

        return rtn

    def _get_preamble(self, start_num):        
        return self.cipher[start_num:start_num + self.PREAMBLE_LENGTH]

    def _valid_numbers(self, input_list) -> list:
        rtn = []
        for i in range(len(input_list)):
            first = input_list[i]
            for j in range(1, len(input_list[i:])):
                second = input_list[i+j]
                rtn.append(first + second)

        return rtn

    def get_valid_numbers(self):
        preamble = self._get_preamble(0)
        return self._valid_numbers(preamble)

    def find_bad_number(self):
        ## 1. define the preamble
        ## 2. get the list of valid numbers
        ## 3. look at the first number after the preamble.
            ## if it is valid, continue. if not, exit returning the bad number
        bad_num_found = False
        i = 0
        while not bad_num_found:
            preamble = self._get_preamble(i)
            valid_numbers = self._valid_numbers(preamble)
            number_to_check = self.cipher[i + self.PREAMBLE_LENGTH]
            if number_to_check not in valid_numbers:
                return number_to_check

            i += 1

    def get_weakness(self):
        bad_number = self.find_bad_number()
        cont_range = []      

        i, j = 0, 1
        total = 0
        while total != bad_number:
            cont_range.append(self.cipher[i])
            #cont_range.append(self.cipher[j])
            total = sum(cont_range)

            while total < bad_number:
                cont_range.append(self.cipher[j])
                total = sum(cont_range)
                j += 1

            ##total should be at least equal to the bad number at this point.
            ## if it is equal, it will skip this and terminate the loop
            ## if it isn't equal, we clear the contiguous range, increment
            ## everything by one, and start again
            if total != bad_number:
                i += 1
                j = i + 1
                cont_range.clear()
                
        smallest, largest = min(cont_range), max(cont_range)
    
        return smallest + largest
        
                

if __name__ == '__main__':
    
    xmas = XMASCipher(INPUT_FILE)
    print('bad number:', xmas.find_bad_number())
    print('cipher weakness:', xmas.get_weakness())
