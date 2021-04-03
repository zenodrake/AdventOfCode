import time

"""
INSTRUCTIONS

After saving Christmas five years in a row, you've decided to take a vacation at a nice resort on a tropical island. Surely, Christmas will go on without you.

The tropical island has its own currency and is entirely cash-only. The gold coins used there have a little picture of a starfish; the locals just call them stars. None of the currency exchanges seem to have heard of them, but somehow, you'll need to find fifty of these coins by the time you arrive so you can pay the deposit on your room.

To save your vacation, you need to get all fifty stars by December 25th.

Collect stars by solving puzzles. Two puzzles will be made available on each day in the Advent calendar; the second puzzle is unlocked when you complete the first. Each puzzle grants one star. Good luck!

Before you leave, the Elves in accounting just need you to fix your expense report (your puzzle input); apparently, something isn't quite adding up.

Specifically, they need you to find the two entries that sum to 2020 and then multiply those two numbers together.

For example, suppose your expense report contained the following:

1721
979
366
299
675
1456

In this list, the two entries that sum to 2020 are 1721 and 299. Multiplying them together produces 1721 * 299 = 514579, so the correct answer is 514579.

Of course, your expense report is much larger. Find the two entries that sum to 2020; what do you get if you multiply them together?

Your puzzle answer was REDACTED.

--- Part Two ---

The Elves in accounting are thankful for your help; one of them even offers you a starfish coin they had left over from a past vacation. They offer you a second one if you can find three numbers in your expense report that meet the same criteria.

Using the above example again, the three entries that sum to 2020 are 979, 366, and 675. Multiplying them together produces the answer, 241861950.

In your expense report, what is the product of the three entries that sum to 2020?

Your puzzle answer was REDACTED.
"""



class EntrySummer:
    def __init__(self, file):
        self.file = file
        with open(self.file) as e:
            self.entries = [int(line) for line in e.readlines()]




    def two_plus(self):
        steps = 0
        now = time.time()
        for i in range(len(self.entries)):
            first = self.entries[i]
            for j in range(1, len(self.entries[i:])):
                second = self.entries[j+i]
                steps += 1
                then = time.time()
                if first + second == 2020:
                    print('two entries')
                    return first, second, first*second, steps, then - now

    def two_plus_sorted(self):
        now = time.time()
        steps = 0
        entries = sorted(self.entries)
        smallest = entries[0]
        largest = entries[-1]
        rest = [i for i in filter(lambda x: 2020 - x > smallest, entries[1:-2])]
        # print(smallest, largest, len(rest))
        # print(rest)
        for i in range(len(rest)):
            first = rest[i]
            for j in range(1, len(rest[i:])):
                second = rest[i+j]
                steps +=1
                then = time.time()
                if first + second == 2020:
                    print('two entries, sorted')

                    return first, second, first*second, steps, then - now

    def three_plus(self):
        now = time.time()
        steps = 0
        for i in range(len(self.entries)):
            first = self.entries[i]
            for j in range(1,len(self.entries[i:])):
                second = self.entries[i+j]
                for k in range(1,len(self.entries[i+1:])):
                    third = self.entries[k]
                    steps += 1
                    then = time.time()
                    if first + second + third == 2020:
                        print('three entries')
                        return first, second, third, first*second*third, steps, then - now


    def three_plus_sorted(self):
        now = time.time()
        entries = sorted(self.entries)
        smallest = entries[0]
        next_smallest = entries[1]
        rest = [i for i in filter(lambda x: 2020 - x >= smallest+next_smallest, entries[2:])]
        rest = [next_smallest] + rest
        steps = 0
        for i in range(len(rest)):
            first = rest[i]
            for j in range(1, len(rest[i:])):
                second = rest[i + j]
                for k in range(1, len(rest[i + 1:])):
                    third = rest[k]
                    steps += 1
                    then = time.time()
                    if first + second + third == 2020:
                        print('three entries, sorted)')
                        return first, second, third, first * second * third, steps, then - now


if __name__ == '__main__':
    ES = EntrySummer('/home/smoint/PycharmProjects/AdventOfCode/advent_of_code_day_one_input')
    # print(ES.two_plus())
    # print(ES.three_plus())
    # print(ES.two_plus_sorted())
    # print(ES.three_plus_sorted())
