using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GameOfLife
{
    public class GameEngine
    {
        public uint currentGeneration { get; private set; }
        private bool[,] field;
        private readonly int rows;
        private readonly int cols;


        /// <summary>
        /// Game engine constructor. Sets the size of the field and generates the initial map
        /// </summary>
        public GameEngine(int rows, int cols, int density)
        { 
            this.rows = rows;
            this.cols = cols;
            field = new bool[cols, rows];

            Random random = new Random();
            for (int x = 0; x < cols; x++)
            {
                for (int y = 0; y < rows; y++)
                {
                    field[x, y] = random.Next(density) == 0;
                }
            }
        }

        /// <summary>
        /// Counts the neighbors of this cell 
        /// </summary>
        /// <returns>
        /// Returns the number of neighbors of a cell 
        /// </returns>
        private int CountNeighbours(int x, int y)
        {
            int count = 0;
            for (int i = -1; i < 2; i++)
            {
                for (int j = -1; j < 2; j++)
                {
                    var col = (x + i + cols) % cols;
                    var row = (y + j + rows) % rows;

                    bool isSelfChecking = col == x && row == y;
                    var hasLife = field[col, row];

                    if (hasLife && !isSelfChecking)
                        count++;
                }
            }
            return count;
        }

        /// <summary>
        /// Generates a new field
        /// </summary>
        public void NextGeneration()
        {
            var newField = new bool[cols, rows];

            for (int x = 0; x < cols; x++)
            {
                for (int y = 0; y < rows; y++)
                {
                    var neighboursCount = CountNeighbours(x, y);
                    var hasLife = field[x, y];

                    if (!hasLife && neighboursCount == 3)
                        newField[x, y] = true;
                    else if (hasLife && (neighboursCount < 2 || neighboursCount > 3))
                        newField[x, y] = false;
                    else
                        newField[x, y] = field[x, y];
                }
            }
            field = newField;
            currentGeneration++;
        }

        /// <returns>
        /// Returns a copy of the given field 
        /// </returns>
        public bool[,] GetCurrentGeneration()
        {
            var result = new bool[cols, rows];
            for (int x = 0; x < cols; x++)
                for (int y = 0; y < rows; y++)
                    result[x, y] = field[x, y];

            return result;
        }

        /// <summary>
        /// Checking the cage for whether it has crawled out of the size of the field
        /// </summary>
        private bool ValidateCellPosition(int x, int y)
        {
            return x >= 0 && y >= 0 && x < cols && y < rows;
        }

        /// <summary>
        /// Creates or removes a cell
        /// </summary>
        private void UpdateCell(int x, int y, bool state)
        {
            if (ValidateCellPosition(x, y))
                field[x, y] = state;
        }

        /// <summary>
        /// Adds a new cell to the field 
        /// </summary>
        public void AddCell(int x, int y)
        {
            UpdateCell(x, y, state: true);
        }

        /// <summary>
        /// Removes a cell from the field
        /// </summary
        public void RemoveCell(int x, int y)
        {
            UpdateCell(x, y, state: false);
        }
    }
}
