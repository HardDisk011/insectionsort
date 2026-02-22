import time

def leng(file):
    with open(file, "r") as f:
        line = sum(1 for _ in f)
        return line
    
def number(file):
    with open(file, "r") as f:
        numbers = [int(line.strip()) for line in f]
        return numbers

def sort(numbers):
    numbersort = []
    for n in numbers:
        inserted = False
        
        for i in range(len(numbersort)):
            if n < numbersort[i]:
                numbersort.insert(i, n)
                inserted = True
                break
        
        if not inserted:
            numbersort.append(n)
    return numbersort

def filegen(array):
    with open("result.txt", "w") as f:
        for value in array:
            f.write(f"{value}\n")



file = input("file name: ")
length = leng(file)
numbers = number(file)
start_time = time.time()  
array = sort(numbers)
end_time = time.time() 
filegen(array)
print("file sorted successfully.")
print(f"The sorting lasted {end_time - start_time:.5f} seconds.")




