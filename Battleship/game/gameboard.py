from texttable import Texttable

class gameboard():
    def __init__(self, board_rows: int, board_columns: int):
        self._board_rows = board_rows
        self._board_columns = board_columns
        self.board = [['0' for iterate_variable in range(self._board_columns)] for index in range(self._board_rows)]
        self.computer_actions = [['0' for iterate_variable in range(self._board_columns)] for index in range(self._board_rows)]

    def place_bomb(self, symbol, bomb_row: int, bomb_column: int):
        self.board[bomb_row][bomb_column] = symbol

    def verify_if_bomb_inside_board(self, row, column):
        if row > self._board_rows or row < 0 or column > self._board_columns or column < 0:
            raise Exception("Invalid bomb position")

    def place_ship(self, chosen_row: int, chosen_column: int, facing_direction, symbol: str):
        if chosen_row < 0 or chosen_row >= self._board_rows or chosen_column < 0 or chosen_column >= self._board_columns:
            raise Exception("Invalid position")
        if facing_direction == 'vertical':
            if chosen_row < 1 or chosen_row >= self._board_rows - 1 or chosen_column < 0 or chosen_column >= self._board_columns:
                raise Exception("Invalid position")
            for position in [-1, 0, 1]:
                if self.board[chosen_row + position][chosen_column] in ['C', 'S']:
                    raise Exception("Overlapping ships")
            self.board[chosen_row][chosen_column] = symbol
            self.board[chosen_row - 1][chosen_column] = symbol
            self.board[chosen_row + 1][chosen_column] = symbol
        if facing_direction == 'horizontal':
            if chosen_row < 0 or chosen_row >= self._board_rows or chosen_column < 1 or chosen_column >= self._board_columns - 1:
                raise Exception("Invalid position")
            for position in [-1, 0, 1]:
                if self.board[chosen_row][chosen_column + position] in ['C', 'S']:
                    raise Exception("Overlapping ships")
            self.board[chosen_row][chosen_column] = symbol
            self.board[chosen_row][chosen_column + 1] = symbol
            self.board[chosen_row][chosen_column - 1] = symbol
    def update_computer_actions(self, row, column):
        self.computer_actions[row][column] = '1'

    def get_rows(self) -> int:
        return self._board_rows

    def get_columns(self) -> int:
        return self._board_columns

    def __str__(self):
        texttable_representation_of_board = Texttable()
        header = ['X']
        for index in range(self._board_columns):
            header.append(chr(ord('A') + index))
        texttable_representation_of_board.header(header)
        for row in range(self._board_rows):
            row_to_be_printed = []
            for column in range(self._board_columns):
                if self.board[row][column] == 'S':
                    row_to_be_printed.append('S')
                elif self.board[row][column] == 'X':
                    row_to_be_printed.append('X')
                elif self.board[row][column] == 'M':
                    row_to_be_printed.append('M')
                else:
                    row_to_be_printed.append(' ')
            texttable_representation_of_board.add_row([str(row + 1)] + row_to_be_printed)
            #texttable_representation_of_board.add_row([str(index + 1)] + [" "] * self._board_cols)

        return texttable_representation_of_board.draw()
    def get_symbol_on_board(self, row, column):
        return self.board[row][column]
    def get_previous_computer_action(self, row, column):
        return self.computer_actions[row][column]
    def __repr__(self):
        return str(self)