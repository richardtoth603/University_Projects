from game.gameboard import gameboard
from random import randint

class game_management():
    def __init__(self):
        self._gameboard = gameboard(10, 10)
        self._number_of_human_hits = 0
        self._number_of_computer_hits = 0
        self._previous_computer_hit = {'row': 0, 'column': 0}
        self._number_of_consecutive_computer_hits = 0
    def _check_if_someone_won(self):
        win_message = ('Not yet', False)
        if self._number_of_human_hits == 9:
            win_message = ('Human won!', True)
        if self._number_of_computer_hits == 9:
            win_message = ("Computer won!", True)
        return win_message
    def pass_gameboard(self):
        return self._gameboard
    def human_place_ship(self, row, column, facing):
        self._gameboard.place_ship(row, column, facing, 'S')
    def computer_place_ship(self):
        number_of_ships_placed = 0
        while number_of_ships_placed < 3:
            row = randint(0, 9)
            column = randint(0, 9)
            directions = ('vertical', 'horizontal')
            direction_choice = randint(0, 1)
            try:
                self._gameboard.place_ship(row, column, directions[direction_choice], 'C')
            except Exception:
                continue
            number_of_ships_placed += 1
    def place_bomb(self, row: int, column: int):
        self._gameboard.verify_if_bomb_inside_board(row, column)
        symbol_on_board = self._gameboard.get_symbol_on_board(row, column)
        if symbol_on_board == 'S':
            raise Exception("Cannot hit your own ships")
        if symbol_on_board == 'C':
            self._place_hit('X', row, column)
            self._number_of_human_hits += 1
            win_condition = self._check_if_someone_won()
            return win_condition
        else:
            self._place_hit('M', row, column)
            return (' ', False)
    def computer_ai(self):
        if self._number_of_consecutive_computer_hits != 0:
            if self._number_of_consecutive_computer_hits == 1:
                for direction in [-1, 1]:
                    if self._gameboard.get_previous_computer_action(self._previous_computer_hit['row'] + direction, self._previous_computer_hit['column']) == '0':
                        if self._gameboard.get_symbol_on_board(self._previous_computer_hit['row'] + direction, self._previous_computer_hit['column']) == 'C':
                            continue
                        elif self._gameboard.get_symbol_on_board(self._previous_computer_hit['row'] + direction, self._previous_computer_hit['column']) == 'S':
                            self._previous_computer_hit['row'] += direction
                            self._number_of_consecutive_computer_hits += 1
                            self._place_hit('X', self._previous_computer_hit['row'], self._previous_computer_hit['column'])
                            self._gameboard.update_computer_actions(self._previous_computer_hit['row'], self._previous_computer_hit['column'])
                            self._number_of_computer_hits += 1
                            return (' ', False) #should go to human move
                        elif self._gameboard.get_symbol_on_board(self._previous_computer_hit['row'] + direction, self._previous_computer_hit['column']) == 'M':
                            continue
                        elif self._gameboard.get_symbol_on_board(self._previous_computer_hit['row'] + direction, self._previous_computer_hit['column']) == 'X':
                            continue
                        else:
                            self._place_hit('M', self._previous_computer_hit['row'] + direction, self._previous_computer_hit['column'])
                            self._gameboard.update_computer_actions(self._previous_computer_hit['row'] + direction, self._previous_computer_hit['column'])
                            return (' ', False)
                            pass

                for direction in [-1, 1]:
                    #implement same here
                    if self._gameboard.get_previous_computer_action(self._previous_computer_hit['row'], self._previous_computer_hit['column'] + direction) == '0':
                        if self._gameboard.get_symbol_on_board(self._previous_computer_hit['row'], self._previous_computer_hit['column'] + direction) == 'C':
                            return (' ', False)
                        elif self._gameboard.get_symbol_on_board(self._previous_computer_hit['row'], self._previous_computer_hit['column'] + direction) == 'S':
                            self._previous_computer_hit['column'] += direction
                            self._number_of_consecutive_computer_hits += 1
                            self._number_of_computer_hits += 1
                            self._place_hit('X', self._previous_computer_hit['row'], self._previous_computer_hit['column'])
                            self._gameboard.update_computer_actions(self._previous_computer_hit['row'], self._previous_computer_hit['column'])
                            return (' ', False) #should go to human move
                        elif self._gameboard.get_symbol_on_board(self._previous_computer_hit['row'], self._previous_computer_hit['column'] + direction) == 'M':
                            continue
                        elif self._gameboard.get_symbol_on_board(self._previous_computer_hit['row'], self._previous_computer_hit['column'] + direction) == 'X':
                            continue
                        else:
                            self._place_hit('M', self._previous_computer_hit['row'], self._previous_computer_hit['column'] + direction)
                            self._gameboard.update_computer_actions(self._previous_computer_hit['row'], self._previous_computer_hit['column'] + direction)
                            return (' ', False)
            if self._number_of_consecutive_computer_hits == 2:
                row_for_last_hit = self._previous_computer_hit['row']
                column_for_last_hit = self._previous_computer_hit['column']
                if self._gameboard.get_previous_computer_action(row_for_last_hit - 1, column_for_last_hit) == '1':
                    if self._gameboard.get_symbol_on_board(row_for_last_hit - 1, column_for_last_hit) == 'X':
                        self._number_of_computer_hits += 1
                        self._number_of_consecutive_computer_hits = 0
                        self._place_hit('X', row_for_last_hit + 1, column_for_last_hit)
                        self._gameboard.update_computer_actions(row_for_last_hit + 1, column_for_last_hit)
                if self._gameboard.get_previous_computer_action(row_for_last_hit + 1, column_for_last_hit) == '1':
                    if self._gameboard.get_symbol_on_board(row_for_last_hit + 1, column_for_last_hit) == 'X':
                        self._number_of_computer_hits += 1
                        self._number_of_consecutive_computer_hits = 0
                        self._place_hit('X', row_for_last_hit - 1, column_for_last_hit)
                        self._gameboard.update_computer_actions(row_for_last_hit - 1, column_for_last_hit)
                if self._gameboard.get_previous_computer_action(row_for_last_hit, column_for_last_hit - 1) == '1':
                    if self._gameboard.get_symbol_on_board(row_for_last_hit, column_for_last_hit - 1) == 'X':
                        self._number_of_computer_hits += 1
                        self._number_of_consecutive_computer_hits = 0
                        self._place_hit('X', row_for_last_hit, column_for_last_hit + 1)
                        self._gameboard.update_computer_actions(row_for_last_hit, column_for_last_hit + 1)
                if self._gameboard.get_previous_computer_action(row_for_last_hit, column_for_last_hit + 1) == '1':
                    if self._gameboard.get_symbol_on_board(row_for_last_hit, column_for_last_hit + 1) == 'X':
                        self._number_of_computer_hits += 1
                        self._number_of_consecutive_computer_hits = 0
                        self._place_hit('X', row_for_last_hit, column_for_last_hit - 1)
                        self._gameboard.update_computer_actions(row_for_last_hit, column_for_last_hit - 1)
                win_condition = self._check_if_someone_won()
                return win_condition


        check_if_bomb_can_be_placed = False
        while check_if_bomb_can_be_placed is False:
            random_row = randint(0, self._gameboard.get_rows() - 1)
            random_column = randint(0, self._gameboard.get_columns() - 1)
            if self._gameboard.get_previous_computer_action(random_row, random_column) == '0':
                if self._gameboard.get_symbol_on_board(random_row, random_column) == 'C':
                    continue
                elif self._gameboard.get_symbol_on_board(random_row, random_column) in ['M', 'X']:
                    continue
                elif self._gameboard.get_symbol_on_board(random_row, random_column) == '0':
                    check_if_bomb_can_be_placed = True
                    self._place_hit('M', random_row, random_column)
                    self._gameboard.update_computer_actions(random_row, random_column)
                    return (' ', False)
                elif self._gameboard.get_symbol_on_board(random_row, random_column) == 'S':
                    check_if_bomb_can_be_placed = True
                    self._place_hit('X', random_row, random_column)
                    self._previous_computer_hit['row'] = random_row
                    self._previous_computer_hit['column'] = random_column
                    self._number_of_consecutive_computer_hits = 1
                    self._number_of_computer_hits +=1
                    self._gameboard.update_computer_actions(random_row, random_column)
                    return (' ', False)
                    #Go to human move
        pass
    def _place_hit(self, symbol, row, column):
        self._gameboard.place_bomb(symbol, row, column)
        pass