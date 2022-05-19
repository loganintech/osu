import sys

def generate_table(size):
    table = []
    for i in range(size):
        temp_list = []
        for x in range(size):
            temp_list.append(-1)
        table.append(temp_list)

    for row in range(size):
        for column in range(size):
            table[row][column] = row * column
    return table

def print_table(table):
    for row in table:
        for column in row:
            print(column, end=" | ")

        print("", end="\n")

def main(table_size):
    print_table(generate_table(table_size))

if __name__ == "__main__":
    main(int(sys.argv[1]))
