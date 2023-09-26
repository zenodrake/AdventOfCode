import re

# ----- PART ONE ----- #
# loop through the list of rules
# find bags which directly contain my_bag
# then find bags which find those bags
# repeat until there are no bags found


input_file_path = '/InputFiles/day_seven_input'
# input_file_path = '/home/smoint/thingus'
my_bag = 'shiny gold'
bag_rules_file = open(input_file_path)
match_rule = re.compile('[a-z]+ [a-z]+ bag')
match_count_rule = re.compile('[1-9]+ [a-z]+ [a-z]+')
direct_holds = []

def find_containing_bags(initial_list):
    #print(len(initial_list))
    if len(initial_list) == 0:
        return initial_list
    else:
        bag_rules_file.seek(0)
        rtn = []
        for line in bag_rules_file:
            for bag in initial_list:
                if bag in line[1:]:
                    rtn.append(match_rule.match(line).group())
        return initial_list + find_containing_bags(rtn)


all_bags = find_containing_bags([my_bag])
duplicate_bags = [bag for bag in all_bags if all_bags.count(bag) > 1]
print("Bag colors which can eventually contain at least one", my_bag, ": ", len(set(all_bags))-1) # to not include the first bag
# print(set(all_bags))
# -----END OF PART ONE----- #


# -----PART TWO ----- #
# find the bags which my_bag must contain.
# then find the bags which those bags contain. repeat until no more bags
#

# all_bags_dict = {}
# bag_dict = {}
# bag_rules_file.seek(0)
# for line in bag_rules_file:
#     if line.startswith(my_bag):
#         abc = line.split('bag')
#         for a in abc:
#             # print(a)
#             match = match_count_rule.search(a)
#             if match:
#                 bag_count = int(match.group()[0])
#                 bag_name = match.group()[2:]
#                 # print(bag_count, bag_name)
#                 if bag_name in bag_dict:
#                     bag_dict[bag_name] += bag_count
#                 else:
#                     bag_dict[bag_name] = bag_count
#
# all_bags_dict = bag_dict.copy()
# # print(bag_dict)
#
# # second level of recursion
# bag_rules_file.seek(0)
# for line in bag_rules_file:
#     for k,v in bag_dict.items():
#         if line.startswith(k):
#             abc = line.split('bag')
#             for a in abc:
#                 match = match_count_rule.search(a)
#                 if match:
#
#                     bag_count = int(match.group()[0])
#                     bag_name = match.group()[2:]
#                     print(bag_count, bag_name)
#                     if bag_name in all_bags_dict:
#                         all_bags_dict[bag_name] += bag_count * v
#                     else:
#                         all_bags_dict[bag_name] = bag_count



def find_containing_bags_count(initial_bag_dict, iterations):
    if len(initial_bag_dict) == 0:
        return initial_bag_dict
    else:
        bag_dict = {}
        bag_rules_file.seek(0)
        for line in bag_rules_file:
            for k,v in initial_bag_dict.items():
                if line.startswith(k):
                    bag_list = line.split('bag')
                    for bag in bag_list:
                        match = match_count_rule.search(bag)
                        if match:
                            bag_count = int(match.group()[0])
                            bag_name = match.group()[2:]

                            # if we just have bag_dict[bag_name] = bag_count * v, then if the bags on the previous
                            # iteration contain some of the same bags this iteration, one of those will be lost
                            if bag_name in bag_dict:
                                bag_dict[bag_name] += bag_count * v
                            else:
                                bag_dict[bag_name] = bag_count * v

                            # print(k, bag_dict)
                            # if bag_name == 'mirrored lavender':
                            #     print("parent bag:", k, ". parent count: ", v, "current count: ", bag_count, ". total: ", bag_count * v)
                            if bag_name in all_bags_dict:
                                all_bags_dict[bag_name] += bag_count * v
                            else:
                                all_bags_dict[bag_name] = bag_count * v
        # print("end of iteration", iterations)
        find_containing_bags_count(bag_dict, iterations+1)

all_bags_dict = {}
find_containing_bags_count({my_bag: 1}, 0)
# print(all_bags_dict)
bags_in_my_bag = sum(all_bags_dict.values())
print(f'bags in my {my_bag} bag: {bags_in_my_bag}')