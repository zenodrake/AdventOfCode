class SeatFinder:
    def __init__(self):
        self.row_tree = self.build_row_tree()
        self.col_tree = self.build_col_tree()

    def get_seat_id(self, boarding_pass):
        row = self.get_row(boarding_pass)
        col = self.get_col(boarding_pass)
        return row * 8 + col

    def get_row(self, boarding_pass):
        a = boarding_pass[0]
        b = boarding_pass[1]
        c = boarding_pass[2]
        d = boarding_pass[3]
        e = boarding_pass[4]
        f = boarding_pass[5]
        g = boarding_pass[6]
        return self.row_tree[a][b][c][d][e][f][g]

    def get_col(self, boarding_pass):
        a = boarding_pass[7]
        b = boarding_pass[8]
        c = boarding_pass[9]
        return self.col_tree[a][b][c]

    def build_row_tree(self):
        return self.__build_tree(0, 127, 'F', 'B')

    def build_col_tree(self):
        return self.__build_tree(0, 7, 'L', 'R')

    def __build_tree(self,start, end, lower_char, upper_char):
        tree = {}
        if start > end:
            return -1
        if end - start == 1:
            return {lower_char: start, upper_char: end}
        return {lower_char: self.__build_tree(start, start + int((end - start) / 2), lower_char, upper_char),
                upper_char: self.__build_tree(end - int((end - start) / 2), end, lower_char, upper_char)}



if __name__ == '__main__':
    boarding_pass_file = '/home/smoint/Documents/PythonStuff/AdventOfCode/InputFiles/day_five_input'
    sf = SeatFinder()
    seat_ids = []

    with open(boarding_pass_file, mode='r') as boarding_passes:
        for boarding_pass in boarding_passes:
            seat_id = sf.get_seat_id(boarding_pass)
            seat_ids.append(seat_id)


    print(max(seat_ids))
    print(sorted(seat_ids))
    print(len(seat_ids))

    min_seat = min(seat_ids)
    max_seat = max(seat_ids)

    sorted_seats = sorted(seat_ids)

    for i in range(len(seat_ids)+1):
        if sorted_seats[i] == min_seat + i:
            pass
        else:
            print(sorted_seats[i], min_seat + i)
            break






