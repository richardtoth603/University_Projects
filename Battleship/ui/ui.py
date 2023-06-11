from game.game import game_management


class ui():
    def __init__(self):
        print("Welcome to Battleship!")
        self._game_manager = game_management()
        print(self._game_manager.pass_gameboard())

    def place_ship(self):
        number_of_placements = 0
        while number_of_placements < 3:
            try:
                row = int(input("row: "))
                column = input("column: ")
                if column not in 'ABCEDFGHIJ':
                    raise Exception("Incorrect input")
                decimal_interpretation_of_letter = 0
                for letter in 'ABCDEFGHIJ':
                    decimal_interpretation_of_letter += 1
                    if column == letter:
                        break
                column = decimal_interpretation_of_letter
                facing = int(input("0 for vertical 1 for horizontal: "))
                directions = ('vertical', 'horizontal')
                self._game_manager.human_place_ship(row-1, column-1, directions[facing])
                number_of_placements += 1
                print(self._game_manager.pass_gameboard())
            except Exception as error:
                print(error)
        self._game_manager.computer_place_ship()
        print(self._game_manager.pass_gameboard())
    def human_place_bomb(self):
        print("Place bomb")
        try:
            row_for_bomb = int(input("row: "))
            column_for_bomb = input("column: ")
            decimal_interpretation_of_letter = 0
            for letter in 'ABCDEFGHIJ':
                decimal_interpretation_of_letter += 1
                if column_for_bomb == letter:
                    break
            column_for_bomb = decimal_interpretation_of_letter
            win_condition = self._game_manager.place_bomb(row_for_bomb-1, column_for_bomb-1)
            print(self._game_manager.pass_gameboard())
            if win_condition[1] == True:
                return win_condition
            win_condition = self._game_manager.computer_ai()
            print(self._game_manager.pass_gameboard())
            if win_condition[1] == True:
                return win_condition
            return win_condition
        except Exception as error:
            print(error)
            self.human_place_bomb()

test_ui = ui()
test_ui.place_ship()

win_condition = ('', False)
while win_condition[1] is False:
    win_condition = test_ui.human_place_bomb()
    if win_condition[1] == True:
        print(win_condition[0])
