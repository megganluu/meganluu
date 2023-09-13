"""
***************************************************************************
Filename:      lab8.py

Author:        Megan Luu

Date:          2023-6-22

Modifications: None

Description:    This module creates 3 dictionaries of cake recipes and lists to create objects of class cake
                which has the following attributes and methods:
                1) Constructor - creates and initializes cake with specified type, size, recipe, and labels
                2) str - returns a value to print pre-formatted
                3) calculateIngredients - returns a list of 2 embedded lists of the ingredient names and
                   ingredient weights
                By using a class, multiple methods, and passing different data values as arguments,
                this program is a more efficient and upgraded version of its predecessor lab 7.
***************************************************************************
"""

class Cake:
    """
        ***************************************************************************

        Class:   Cake

        Methods:
            1) __init__ - constructor
            2) __str__ - print method
            3) calculateIngredients - creates list of ingredient names and weights for the object

        Author:  Megan Luu

        Date:    2023-6-22

        Description:
        This class is the blueprint for objects that have the following attributes:
            1) Cake flavor
            2) Cake size
            3) Recipe

        ***************************************************************************
        """
    def __init__(self, type, size):
        """
            ***************************************************************************

            Method:   __init__(self, type, size)

            Parameters:
                        self - object under scope
                        type - numerical code of the cake type
                        size - char code of the cake size

            Outputs: Nothing

            Returns: Nothing

            Author:  Megan Luu

            Date:    2023-6-22

            Description:
            This method is the constructor and initializes all attributes of the object. It has 3 dictionaries, and a
            list of dictionaries that are used to define the recipe and ingredients of the object. It calls the
            calculateIngredients method to assist it.

            ***************************************************************************
            """

        chocRecipe = {'Flour': 0.158, 'Sugar': 0.245, 'Unsweetened Cocoa Powder': 0.056, 'Baking Powder': 0.004,
                      'Baking Soda': 0.006, 'Salt': 0.004, 'Egg': 0.09, 'Buttermilk': 0.18, 'Oil': 0.081,
                      'Vanilla Extract': 0.006, 'Boiling Water': 0.17}

        redVRecipe = {'Flour': 0.224, 'Sugar': 0.224, 'Unsweetened Cocoa Powder': 0.004,
                      'Baking Soda': 0.007, 'Salt': 0.004, 'Egg': 0.09, 'Buttermilk': 0.179, 'Oil': 0.24,
                      'Vanilla Extract': 0.003, 'Red Food Coloring': 0.021, 'Distilled Vinegar': 0.004}

        lemonRecipe = {'Sugar': 0.15, 'Egg': 0.09, 'Buttermilk': 0.09, 'Vanilla Extract': 0.002,
                       'Butter': 0.085, 'Sifted Self-Rising Flour': 0.156, 'Filling - Egg Yolk': 0.179,
                       'Filling - Sugar': 0.113, 'Filling - Butter': 0.021, 'Filling - Lemon Juice and Zest': 0.114}
        cakeDictionary = [chocRecipe, redVRecipe, lemonRecipe]

        self.type = type
        self.size = size
        typeList = ["Chocolate", "Red Velvet", "Lemon"]
        if self.size == 'r' or self.size == 'R':
            self.weight = 64
            self.sizeLabel = "Regular"
        else:
            self.weight = 112
            self.sizeLabel = "Large"
        self.name = typeList[type - 1]
        self.recipe = cakeDictionary[type - 1]
        self.ingrdList = self.calculateIngredients(self.weight, self.recipe)

    def __str__(self):
        """
            ***************************************************************************

            Method:   __str__(self)

            Parameters: self - object under scope

            Outputs: Nothing

            Returns: List of strings to print

            Author:  Megan Luu

            Date:    2023-6-22

            Description:
            This function creates a list of strings with formatting and uses a loop to add each ingredient to the
            list. It then returns the string list to print.

            ***************************************************************************
            """
        string = ["%s %s Cake Ingredient List\n" % (self.sizeLabel, self.name)]
        index = 0
        total = 0
        for ingredientName in self.ingrdList[0]:
            string.append(f"%-35s%5.1f Oz" % (ingredientName + ":", self.ingrdList[1][index]))
            total += self.ingrdList[1][index]
            index += 1
        string.append(f"\n%-35s%5.1f Oz\n" % ("Total", total))
        return "\n".join(string)

    def calculateIngredients(self, weight, recipe):
        """
            ***************************************************************************

            Method:   calculateIngredients(self, weight, recipe)

            Parameters:
                        self - object under scope
                        weight - total weight of the cake
                        recipe - dictionary of ingredients and percentages for specified cake

            Outputs: Nothing

            Returns: Nested list of name and weight for each ingredient

            Author:  Megan Luu

            Date:    2023-6-22

            Description:
            This function creates 3 lists, uses a dictionary of name and weight percentages for each ingredient, and
            uses a for loop to build a list of ingredient labels and list of ingredient weights. It then adds these
            lists as two elements in a larger list.
            The loop is dependent on how many keys are in the dictionary.

            ***************************************************************************
            """
        # creates empty list
        ingredients = []
        list1 = []
        list2 = []
        for ingredientLabel, ingredientWt in recipe.items():
            list1.append(ingredientLabel)
            list2.append(recipe[ingredientLabel] * weight)

        ingredients.append(list1)
        ingredients.append(list2)
        return ingredients

""" 
**********************************************
        Create and print cake objects 
**********************************************
"""
reg_chocolate_cake = Cake(1,'R')
lrg_chocolate_cake = Cake(1,'L')
reg_red_velvet_cake = Cake(2,'R')
lrg_red_velvet_cake = Cake(2,'L')
reg_lemon_cake = Cake(3,'R')
lrg_lemon_cake = Cake(3,'L')

print(reg_chocolate_cake)
print(lrg_chocolate_cake)
print(reg_red_velvet_cake)
print(lrg_red_velvet_cake)
print(reg_lemon_cake)
print(lrg_lemon_cake)

"""
************************
       TEST CASES 
************************
Regular Chocolate Cake Ingredient List

Flour:                              10.1 Oz
Sugar:                              15.7 Oz
Unsweetened Cocoa Powder:            3.6 Oz
Baking Powder:                       0.3 Oz
Baking Soda:                         0.4 Oz
Salt:                                0.3 Oz
Egg:                                 5.8 Oz
Buttermilk:                         11.5 Oz
Oil:                                 5.2 Oz
Vanilla Extract:                     0.4 Oz
Boiling Water:                      10.9 Oz

Total                               64.0 Oz

Large Chocolate Cake Ingredient List

Flour:                              17.7 Oz
Sugar:                              27.4 Oz
Unsweetened Cocoa Powder:            6.3 Oz
Baking Powder:                       0.4 Oz
Baking Soda:                         0.7 Oz
Salt:                                0.4 Oz
Egg:                                10.1 Oz
Buttermilk:                         20.2 Oz
Oil:                                 9.1 Oz
Vanilla Extract:                     0.7 Oz
Boiling Water:                      19.0 Oz

Total                              112.0 Oz

Regular Red Velvet Cake Ingredient List

Flour:                              14.3 Oz
Sugar:                              14.3 Oz
Unsweetened Cocoa Powder:            0.3 Oz
Baking Soda:                         0.4 Oz
Salt:                                0.3 Oz
Egg:                                 5.8 Oz
Buttermilk:                         11.5 Oz
Oil:                                15.4 Oz
Vanilla Extract:                     0.2 Oz
Red Food Coloring:                   1.3 Oz
Distilled Vinegar:                   0.3 Oz

Total                               64.0 Oz

Large Red Velvet Cake Ingredient List

Flour:                              25.1 Oz
Sugar:                              25.1 Oz
Unsweetened Cocoa Powder:            0.4 Oz
Baking Soda:                         0.8 Oz
Salt:                                0.4 Oz
Egg:                                10.1 Oz
Buttermilk:                         20.0 Oz
Oil:                                26.9 Oz
Vanilla Extract:                     0.3 Oz
Red Food Coloring:                   2.4 Oz
Distilled Vinegar:                   0.4 Oz

Total                              112.0 Oz

Regular Lemon Cake Ingredient List

Sugar:                               9.6 Oz
Egg:                                 5.8 Oz
Buttermilk:                          5.8 Oz
Vanilla Extract:                     0.1 Oz
Butter:                              5.4 Oz
Sifted Self-Rising Flour:           10.0 Oz
Filling - Egg Yolk:                 11.5 Oz
Filling - Sugar:                     7.2 Oz
Filling - Butter:                    1.3 Oz
Filling - Lemon Juice and Zest:      7.3 Oz

Total                               64.0 Oz

Large Lemon Cake Ingredient List

Sugar:                              16.8 Oz
Egg:                                10.1 Oz
Buttermilk:                         10.1 Oz
Vanilla Extract:                     0.2 Oz
Butter:                              9.5 Oz
Sifted Self-Rising Flour:           17.5 Oz
Filling - Egg Yolk:                 20.0 Oz
Filling - Sugar:                    12.7 Oz
Filling - Butter:                    2.4 Oz
Filling - Lemon Juice and Zest:     12.8 Oz

Total                              112.0 Oz


Process finished with exit code 0
"""