




##steps:
        ##1. read all input into a variable as a long string
        ##2. split that string on double newlines '\n\n'. this will generate the different groups
        ##3. for each group, create a set of the different answers, not including the newline character
        ##      >>> answers = {a for a in group if a != '\n'}
        ##      >>> answers = set(group)
        ##4. calculate how many people are in the group
        ##      >>> people_in_group = len(group.split('\n'))
        ##      >>> people_in_group = group.count('\n') + 1
        ##5. create an answers dictionary from this set where the keys are the answers; the values are 0
        ##      >>> answers_dict = dict(zip(answers, [0 for i in range(people_in_group)]))
        ##6. loop over every character in group updating the dictionary with the counts for each
        ##      >>> for a in group:
        ##         answers_dict[a] += 1
        ##7. remove the new line character from the dictionary
        ##      >>> answers_dict.del('\n')
        ##8. calculate the score of each group
        ##      >>> group_score = people_in_group * len([k for k,v in answers_dict.items() if v == people_in_group])
        ##9. the total score is the sum of the group scores


def thingus(FILE):
    
    #FILE = '/home/wrowsers/PythonStuff/AdventOfCode/2020/Inputs/advent_of_code_day_six_input'
    customs_total = 0

    with open(FILE, mode='r') as customs_declaration:
        all_answers = customs_declaration.read()[:-1]
        answers_list = all_answers.split('\n\n')

        for answers_group in answers_list:
            answers = {a for a in answers_group if a != '\n'}

            people_in_group = len(answers_group.split('\n'))
            answers_dict = dict(zip(answers, (0 for i in answers)))

            for a in [a for a in answers_group if a != '\n']:
                answers_dict[a] += 1

            group_score = len([k for k,v in answers_dict.items() if v == people_in_group])
            customs_total += group_score

            print(answers_group)
            print(f'dictionary: {answers_dict}')
            print(sorted([k for k,v in answers_dict.items() if v == people_in_group]))
            print(f'people in group: {people_in_group}')
            print(f'total for group: {group_score}')
            print('~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~')
            print()
            print()


    print(customs_total)
    print(f'number of groups: {len(answers_list)}')

thingus('/home/wrowsers/PythonStuff/AdventOfCode/2020/Inputs/advent_of_code_day_six_input')
