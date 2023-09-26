## 1. read in seating chart from file
## 2. generate the seating structure. this is a bunch of nodes.
##    a seat has a seat left, seat right, seat up, seat down,
##    seat diagonally up left/right, down left/right.
##    a seat also has a status: empty or occupied
##
##    There is also a floor node, which never changes.
##    Floor nodes apparently count as empty seats
##
## 3. apply rules to every seat.
##    if a seat is empty, and all adjacent seats are empty, it becomes occupied
##    if a seat is occupied, and four or more adjacent seats are also occupied, it becomes empty
##    otherwise, the status does not change
## 4. the rules are applied simultaneously, so we have to generate a new seating
##    chart from the old seating chart. the status change of a previous seat
##    cannot influence the rules applied to a later seat
## 5. repeat this process until the seating chart is static and repeated iterations
##    do not generate new seat statuses


import AdventOfCode.helper as h


EMPTY = 0
FULL = 1



class SeatPos(Direction):
    ONE = 0
    TWO = 2
    THREE = 4
    FOUR = 3
    FIVE = 4
    SIX = 5
    SEVEN = 6
    EIGHT = 7
    NINE = 8
    
    UPLEFT = 0
    UP = 1
    UPRIGHT = 2
    LEFT = 3
    MIDDLE = 4
    RIGHT = 5
    DOWNLEFT = 6
    DOWN = 7
    DOWNRIGHT = 8
    
    FIRST = 0
    SECOND = 1
    THIRD = 2
    FOURTH = 3
    FIFTH = 4
    SIXTH = 5
    SEVENTH = 6
    EIGTH = 7
    NINTH = 8
    


class Seat:
    def __init__(self, row, column, seat_num, threshhold):

        ## create the surrounding nodes.
        ## nodes are numbered from 1-9, starting from the top left
        ## 0    1    2
        ## 3    4    5
        ## 6    7    8
        self.seats = [None for i in range(10)]
        self.seats[SeatPos.MIDDLE] = self
        self.row = row
        self.column = column
        self.status = EMPTY
        self.seat_num = seat_num
        self.type = "seat"
        self.threshhold = threshhold


    ##so we can access Seats like this: Node[3] or Node[MIDDLE]
    def __getitem__(self, pos):
        return self.seats[pos]

    ##so we can assign seats like this seat[1] = 'x'
    def __setitem__(self, pos, val):
        self.seats[pos] = val

    def __repr__(self):
        if self.status == EMPTY:
            return "L"
        else:
            return "#"

    ## loop over the adjacent seats. if they are all empty, return true,
    ## otherwise false
    def all_adjacent_empty(self):
        for seat in self.adjacent_seats():

            if seat.status == FULL:
                return False

        return True


    def apply_rules(self):
        
        if self.status == EMPTY and self.all_adjacent_empty():
            self.status = FULL
        elif self.status == FULL and self.num_adjacent_full() >= self.threshhold:
            self.status = EMPTY
        else:
            pass    


    def adjacent_seats(self):
        return [seat for seat in self.seats if seat and seat is not self]


    def num_adjacent_full(self):
        rtn = 0
        for seat in self.adjacent_seats():
            if seat.status == FULL:
                rtn += 1
        return rtn


    ## run the rules for changing the status, but don't actually change it
    ## just return what the status would be
    def get_new_status(self):
            
        if self.status == EMPTY and self.all_adjacent_empty():
            return FULL
        elif self.status == FULL and self.num_adjacent_full() >= self.threshhold:
            return EMPTY

        return self.status




    def stat_y_number(self):
        return self.__repr__() + f"({self.seat_num})"


class Floor(Seat):
    def __init__(self, row, column, seat_num, threshhold):
        super().__init__(row, column, seat_num, threshhold);
        self.status = EMPTY
        self.type = "floor"

    def apply_rules(self):
        self.status = EMPTY

    def get_new_status(self):
        return EMPTY

    def __repr__(self):
        return "."
    


class Plane:
    def __init__(self, chart_path, threshhold):
        self.threshhold = threshhold
        self.rows = 0
        self.columns = self._calc_columns(chart_path)
        self.seating_chart = self._import_seating_chart(chart_path);
        
        

    def _calc_columns(self, file_path):
        ##open the file once to read one line and get hom many columns there are
        f = open(file_path)
        c = len(f.readline())-1
        f.close()
        return c


    def _import_seating_chart(self, file_path):

        ##read the file and assign seats as necessary
        chart = []
        seat_num = 0
        with open(file_path) as f:
            r, c = 0, 0

            for row in f.readlines():
                seats = row[:-1]
                for seat in seats:
                    if seat == "L":
                        chart.append(Seat(r, c, seat_num, self.threshhold))
                    elif seat == ".":
                        chart.append(Floor(r, c, seat_num, self.threshhold))
                        
                    seat_num += 1
                    c += 1
                r += 1
                c = 0 ##reset columns at the start of each row

        self.rows = r
        return self._link_seats(chart)


    def _link_seats(self, seats):
        ## go through all the seats
        for seat in seats:
            if seat.row == 0 and seat.column == 0: ##top left seat
                seat[SeatPos.UPLEFT] = None
                seat[SeatPos.UP] = None
                seat[SeatPos.UPRIGHT] = None
                seat[SeatPos.LEFT] = None
                seat[SeatPos.RIGHT] = seats[seat.column+1]
                seat[SeatPos.DOWNLEFT] = None
                seat[SeatPos.DOWN] = seats[seat.seat_num+self.columns]
                seat[SeatPos.DOWNRIGHT] = seats[seat.seat_num+self.columns+1]

            elif seat.row == 0 and seat.column == self.columns-1: ##top right seat
                seat[SeatPos.UPLEFT] = None
                seat[SeatPos.UP] = None
                seat[SeatPos.UPRIGHT] = None
                seat[SeatPos.LEFT] = seats[seat.seat_num-1]
                seat[SeatPos.RIGHT] = None
                seat[SeatPos.DOWNLEFT] = seats[seat.seat_num-1+self.columns]
                seat[SeatPos.DOWN] = seats[seat.seat_num+self.columns]
                seat[SeatPos.DOWNRIGHT] = None

            elif seat.row == 0: ##first row of seats
                seat[SeatPos.UPLEFT] = None
                seat[SeatPos.UP] = None
                seat[SeatPos.UPRIGHT] = None
                seat[SeatPos.LEFT] = seats[seat.seat_num-1]
                seat[SeatPos.RIGHT] = seats[seat.seat_num+1]
                seat[SeatPos.DOWNLEFT] = seats[seat.seat_num+(self.columns-1)]
                seat[SeatPos.DOWN] = seats[seat.seat_num+self.columns]
                seat[SeatPos.DOWNRIGHT] = seats[seat.seat_num+(self.columns+1)]
                
            elif seat.row == self.rows-1 and seat.column == 0: ##bottom left seat
                seat[SeatPos.UPLEFT] = None
                seat[SeatPos.UP] = seats[seat.seat_num-self.columns]
                seat[SeatPos.UPRIGHT] = seats[seat.seat_num-self.columns+1]
                seat[SeatPos.LEFT] = None
                seat[SeatPos.RIGHT] = seats[seat.seat_num+1]
                seat[SeatPos.DOWNLEFT] = None
                seat[SeatPos.DOWN] = None
                seat[SeatPos.DOWNRIGHT] = None
                
            elif seat.row == self.rows-1 and seat.column == self.columns-1: ##bottom right seat
                seat[SeatPos.UPLEFT] = seats[seat.seat_num-self.columns-1]
                seat[SeatPos.UP] = seats[seat.seat_num-self.columns]
                seat[SeatPos.UPRIGHT] = None
                seat[SeatPos.LEFT] = seats[seat.seat_num-1]
                seat[SeatPos.RIGHT] = None
                seat[SeatPos.DOWNLEFT] = None
                seat[SeatPos.DOWN] = None
                seat[SeatPos.DOWNRIGHT] = None
                
            elif seat.column == 0: ##first column of seats
                seat[SeatPos.UPLEFT] = None
                seat[SeatPos.UP] = seats[seat.seat_num-self.columns]
                seat[SeatPos.UPRIGHT] = seats[seat.seat_num-(self.columns-1)]
                seat[SeatPos.LEFT] = None
                seat[SeatPos.RIGHT] = seats[seat.seat_num+1]
                seat[SeatPos.DOWNLEFT] = None
                seat[SeatPos.DOWN] = seats[seat.seat_num+self.columns]
                seat[SeatPos.DOWNRIGHT] = seats[seat.seat_num+self.columns+1]

            elif seat.column == self.columns-1: ##last column of seats
                seat[SeatPos.UPLEFT] = seats[seat.seat_num-self.columns-1]
                seat[SeatPos.UP] = seats[seat.seat_num-self.columns]
                seat[SeatPos.UPRIGHT] = None
                seat[SeatPos.LEFT] = seats[seat.seat_num-1]
                seat[SeatPos.RIGHT] = None
                seat[SeatPos.DOWNLEFT] = seats[seat.seat_num+self.columns-1]
                seat[SeatPos.DOWN] = seats[seat.seat_num+self.columns]
                seat[SeatPos.DOWNRIGHT] = None
                
            elif seat.row == self.rows-1: ##last row
                seat[SeatPos.UPLEFT] = seats[seat.seat_num-self.columns-1]
                seat[SeatPos.UP] = seats[seat.seat_num-self.columns]
                seat[SeatPos.UPRIGHT] = seats[seat.seat_num-self.columns+1]
                seat[SeatPos.LEFT] = seats[seat.seat_num-1]
                seat[SeatPos.RIGHT] = seats[seat.seat_num+1]
                seat[SeatPos.DOWNLEFT] = None
                seat[SeatPos.DOWN] = None
                seat[SeatPos.DOWNRIGHT] = None

            else: ##all other seats
                seat[SeatPos.UPLEFT] = seats[seat.seat_num-(self.columns-1)]
                seat[SeatPos.UP] = seats[seat.seat_num-self.columns]
                seat[SeatPos.UPRIGHT] = seats[seat.seat_num-(self.columns+1)]
                seat[SeatPos.LEFT] = seats[seat.seat_num-1]
                seat[SeatPos.RIGHT] = seats[seat.seat_num+1]
                seat[SeatPos.DOWNLEFT] = seats[seat.seat_num+(self.columns-1)]
                seat[SeatPos.DOWN] = seats[seat.seat_num+self.columns]
                seat[SeatPos.DOWNRIGHT] = seats[seat.seat_num+(self.columns+1)]

        return seats


    def num_seats_occupied(self):
        return sum((s.status for s in self.seating_chart))

    def apply_rules(self):
        ##apply the rules to each seat.
        ## we need a secondary list here methinks which is just the statuses of each seat

        # track the number of changed seat statuses, then return that number
        new_chart_statuses = [i for i in range(self.rows * self.columns)]
        num_changes = 0
        for seat in self.seating_chart:
            new_status = seat.get_new_status()
            if new_status != seat.status:
                num_changes += 1
            new_chart_statuses[seat.seat_num] = new_status

        ##loop over the seating chart again, this time actually changing the status
        for seat in self.seating_chart:
            seat.status = new_chart_statuses[seat.seat_num]


        return num_changes
            
    def show_seating_chart(self, include_numbers=False):
        seat_num = 0
        for r in range(self.rows):
            for c in range(self.columns):
                s = self.seating_chart[seat_num]
                seat_num += 1
                if include_numbers:
                    print(s.stat_y_number(), end=' ')
                else:
                    print(s, end='')
            print()

    def show_seating_numbers(self):
        seat_num = 0
        with open('/home/wrowsers/thingus', mode='w') as f:
            for r in range(self.rows):
                for c in range(self.columns):
                    s = self.seating_chart[seat_num]
                    next_seat = s.seats[SeatPos.UP]
                    if next_seat:
                        f.write(f"\t{s.seat_num} ({next_seat.seat_num})")
                    else:
                        f.write(f"\t{s.seat_num} (none)")
                    
                    seat_num += 1
                f.write("\n")

    def fill_seats(self, show):

        if show:
            self.show_seating_chart()
                
        num_changed = -1
        num_iterations = 0
        while num_changed != 0:
            num_changed = self.apply_rules()
            num_iterations += 1

        if show:
            print()
            self.show_seating_chart()

        return self.num_seats_occupied()


        
## test file
is_test = True

input_file = h.get_input_file(is_test)


print()
PART_ONE_THRESHHOLD = 4
plane = Plane(input_file, PART_ONE_THRESHHOLD)

num_occupied = plane.fill_seats(show=0)
print(f"final occupied seats for part one: {num_occupied}")




print()
print()
PART_TWO_THRESHHOLD = 5
plane = Plane(input_file, PART_TWO_THRESHHOLD)
num_occupied = plane.fill_seats(show=1)
print(f"final occupied seats for part two: {num_occupied}")

#for part two, we have to look in a line in each direction until we either
#see the end of the plane or until we see a seat. once we see a seat, stop looking
#floors are seen over/through and should be ignored

#I think we can still use _link_seats to get adjacent seats, as we know that functionality works
#to find visible seats, we can look recursively at each adjacent seat going in the same direction
#for example, for a seat smack in the middle, choose the seat in UPLEFT
#if that is a floor, choose the floor's UPLEFT seat
#if the UPLEFT seat is None, we know we're at the edge of the plane

## this can be solved by using geometry. the seat positions are (x,y) coordinates or (r,c) (r, theta)
## each seat can see around it.
##seating chart is thus a two dimensional arry
## to find if a seat can see another seat is equivalent to solving an equation, y=mx+b
## or it could be done geometrically with radius and angle
## y = mx + b == Ax + By + C = 0 == y - y1 = m(x - x1)

## we need a way to add points to one another, so when we subtract the x, the y, or both,
## from the target, if the target coordinates are on the line of vision, then the source seat
## can see the target



class Pos:
	def __init__(self, r, c):
		self.r = r
		self.c = c
	def __add__(self, o):
		if isinstance(o, Pos):
			return Pos(self.r + o.r, self.c + o.c)
		return Pos(self.r + o, self.c + o)
	def __neg__(self):
		return (-self.r, -self.c)
	def __sub__(self, o):
		if isinstance(o, Pos):
			return Pos(self.r - o.r, self.c - o.c)
		return Pos(self.r - o, self.c - o)
	def __eq__(self, o):
		return self.r == o.r and self.c == o.c
	def __repr__(self):
		return str((self.r, self.c))
	def __iadd__(self, o): ##this let's us do Pos += 5 or Pos += Pos
		if isinstance(o, Pos):
			return Pos(self.r + o.r, self.c + o.c)
		return Pos(self.r + o, self.c + o)
	def __isub__(self, o): ##this let's us do Pos -= 5 or Pos -= Pos
		if isinstance(o, Pos):
			return Pos(self.r - o.r, self.c - o.c)
		return Pos(self.r - o, self.c - o)


class Line:
	def __init__(self, p1, p2):
		self.A = p1.c - p2.c
		self.B = p2.r - p1.r
		self.C = -self.A * p1.r - self.B * p1.c
		self.M = -self.A / self.B

    def __eq__(self, o):
		return self.M == o.M and self.C == o.C

    def next_from_point(self, point, direction="p"):
        if direction == "n":            
            x = point.r - 1
            y = self.M * x + (-self.C/self.B)
            return Pos(x, y)
        else:
            x = point.r + 1
            y = self.M * x + (-self.C/self.B)

    def next_n_from_point(self, point, n, direction="p"):
		rtn = []
		p = self.next_from_point(point, direction)
		rtn.append(p)
		for i in range(n-1):
			p = self.next_from_point(p, direction)
			rtn.append(p)
		return rtn



##the above points and lines and stuff is all fun and good, but it's not helping solve the problem
## we need to rejigger the plane's seating chartt to be a two dimensional array
## a seat will be akin to a point and will have vision lines. to get the other seats
## the current seat can see, we will ask the seat to get the next point on each vision line
## while it cannot see anything. the next node in any direction is always one
## in whatever dimension we want. this turns a direction into a group of flags
## akin to (x,y,z...n).  to account for floors, we could have another attribute
## called visible. we need to account for there not being any more seats though
## we could do that by maybe looking at if adjacent seats are None, or perhaps
## in a more cool way, we could give the seat a bounds, by having the plane have a bounds
## then we'd have to check every dimension for bounds checking'



class Direction:
	def __init__(self, dims):
		self.dims = dims
	def max_in_dim(self):
		return max(self.dims)

        
