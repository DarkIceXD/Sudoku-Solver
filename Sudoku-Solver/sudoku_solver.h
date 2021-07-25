#ifndef SUDOKU_SOLVER_H
#define SUDOKU_SOLVER_H

#include <array>
#include <ostream>

class sudoku_solver {
public:
	constexpr sudoku_solver(const std::array<std::array<uint8_t, 9>, 9>& grid) noexcept : grid(grid) { }

	[[nodiscard]] constexpr bool solve() noexcept
	{
		size_t y = 0, x = 0;
		if (!get_empty_cell(y, x))
			return true;

		for (uint8_t number = 1; number <= 9; number++)
		{
			if (is_move_possible(y, x, number))
			{
				grid[y][x] = number;
				if (solve())
					return true;
				grid[y][x] = 0;
			}
		}

		return false;
	}

	[[nodiscard]] constexpr uint8_t get(const size_t y, const size_t x) const noexcept
	{
		return grid[y][x];
	}

private:
	[[nodiscard]] constexpr bool get_empty_cell(size_t& out_y, size_t& out_x) const noexcept
	{
		for (size_t y = 0; y < grid.size(); y++)
		{
			const auto& row = grid[y];
			for (size_t x = 0; x < row.size(); x++)
			{
				if (row[x] == 0)
				{
					out_y = y;
					out_x = x;
					return true;
				}
			}
		}
		return false;
	}

	[[nodiscard]] constexpr bool is_move_possible(const size_t y, const size_t x, const uint8_t number) const noexcept
	{
		for (size_t i = 0; i < grid[y].size(); i++)
		{
			if (grid[y][i] == number)
				return false;
		}

		for (size_t i = 0; i < grid.size(); i++)
		{
			if (grid[i][x] == number)
				return false;
		}

		const auto base_y = y - (y % 3);
		const auto base_x = x - (x % 3);
		for (size_t i = 0; i < 3; i++)
		{
			for (size_t j = 0; j < 3; j++)
			{
				if (grid[base_y + i][base_x + j] == number)
					return false;
			}
		}

		return true;
	}

	std::array<std::array<uint8_t, 9>, 9> grid;

public:
	constexpr friend std::ostream& operator<<(std::ostream& os, const sudoku_solver& sudoku) noexcept
	{
		for (size_t y = 0; y < sudoku.grid.size(); y++)
		{
			if (y > 0 && y % 3 == 0)
				os << "---------------------\n";
			const auto& row = sudoku.grid[y];
			for (size_t x = 0; x < row.size(); x++)
			{
				if (x > 0 && x % 3 == 0)
					os << "| ";
				if (row[x])
					os << static_cast<int>(row[x]) << ' ';
				else
					os << "  ";
			}
			os << '\n';
		}
		return os;
	}
};

#endif
