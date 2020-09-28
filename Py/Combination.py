import itertools

"""
    Notes : the first item of the end list seems always to be the first element
"""

def get_all_possible_order(_ls):
    end_list = []
    for i in itertools.permutations(_ls,len(_ls)):
        end_list.append(i)
    print("All possible combinations")
    print("Total combiantion = {0}".format(len(end_list)))
    input("press to continous")

    return end_list

   
list1 = [9,7,10]
end_list = []
for i in itertools.permutations(list1,3):
    end_list.append(i)

print(end_list)