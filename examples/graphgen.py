# generate strategy
# first, generate all the constants of computation graph

# secondly, generate all the operator vertices of computation graph
# 1. generate 100 random integers set and assign them "label" (may be uuid)
# 2. generate 100 random "add" "mul" "sub" "div" (this is our goal, 100 times computation is a good start)
# 3. pick a arbitrary combination from random integers two operands combination set
# which is generated initially from random integers set (n * (n - 1)/2,
# pick one operand from set and combine with rest of operands)
# 4. generate a uuid (label of operator vertices) and assign to our operator
# 5. arbitrarily pick a operator (from four operators)
# 6. combine with generated uuid in step 4 and all of other existed labels in random integers set,
# and add all the possible combinations to random integers two operands combination set
# 7. add generated uuid in step 4 to random integers set
# 8. execute 100 times from step 3 to step 6


import random
import string
import os.path
from os import path


def genSym(size=6, chars=string.ascii_uppercase + string.digits):
    return ''.join(random.choice(chars) for _ in range(size))


def genConst(f, labelOfConst, actualNumber):
    f.write("@const ")
    f.write("%")
    f.write(labelOfConst + " ")
    f.write(str(actualNumber))
    f.write("\n")


def genOp(f, labelOfOperator, operator, operand1, operand2):
    f.write("@" + operator + " ")
    f.write("%" + labelOfOperator + " ")
    f.write("$" + str(operand1) + " ")
    f.write("$" + str(operand2))
    f.write("\n")


def genOut(f, labelOfOutput, usedLabel):
    f.write("@output %" + labelOfOutput + " $" + usedLabel)
    f.write("\n")


def addNewMemberToRandomNumberListAndRandomCombinationList(generatedId, random_integers_list, combination_tuple_list):
    random_integers_list.append(generatedId)
    for elem in random_integers_list:
        combination_tuple_list.append((generatedId, elem))


if __name__ == "__main__":

    fileName = "complex.sfg"
    # remove file for regenerating
    if path.exists(fileName):
        os.remove(fileName)

    operators = ["add", "mul", "sub", "div"]
    random_integers_list = []
    random_integers_combination_list = []

    f = open(fileName, "a")

    usedLabels = []

    # generate the constants
    for i in range(0, 10):
        generatedId = genSym()
        randomNumber = random.randint(0, 10000)
        genConst(f, generatedId, randomNumber)
        random_integers_list.append(generatedId)
        usedLabels.append(generatedId)

    length = len(usedLabels)

    combination_tuple_list = []

    for i in range(0, length):
        j = i + 1
        for j in range(j, length):
            combination_tuple_list.append((usedLabels[i], usedLabels[j]))

    # generate the function calls
    for i in range(0, 100):
        length = len(combination_tuple_list) - 1
        if (length == 0):
            break
        randomIndex = random.randint(0, length)
        pickedCombination = combination_tuple_list[randomIndex]
        combination_tuple_list.remove(pickedCombination)
        generatedId = genSym()
        generatedOperator = operators[random.randint(0, 3)]

        genOp(f, generatedId, generatedOperator, pickedCombination[0], pickedCombination[1])

        usedLabels.append(generatedId)
        for elem in usedLabels:
            if elem != generatedId:
                combination_tuple_list.append((generatedId, elem))

    # generate outputs
    # for i in range(0, 5):
        # generatedId = genSym()
        # genOut(f, generatedId, usedLabels[random.randint(0, len(usedLabels))])

    f.close()

    # open and read the file after the appending:
    f = open(fileName, "r")
    print(f.read())
