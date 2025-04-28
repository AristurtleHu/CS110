import math

# Calculate the first sum (i=1 to 56)
sum1 = 0
for i in range(1, 57):
    term = math.floor((64 - i) / 2) + (64 - i) - 1
    sum1 += term

# Calculate the second sum (i=57 to 63)
sum2 = 0
for i in range(57, 64):
    term = (64 - i) * 2
    sum2 += term

# Calculate the third sum (denominator, i=1 to 63)
sum3 = 0
for i in range(1, 64):
    term = (64 - i) * 2
    sum3 += term

# Calculate the numerator
numerator = sum1 + sum2

# Calculate the denominator
denominator = sum3

# Calculate the final result, checking for division by zero
if denominator == 0:
    result = "Error: Division by zero"
else:
    result = numerator / denominator

# Print the result
print(f"Sum 1 (i=1 to 56): {sum1}")
print(f"Sum 2 (i=57 to 63): {sum2}")
print(f"Numerator (Sum 1 + Sum 2): {numerator}")
print(f"Denominator (Sum 3, i=1 to 63): {denominator}")
print(f"Result: {result}")

# Alternative calculation using list comprehensions (more concise)
# sum1_comp = sum(math.floor((64 - i) / 2) + 64 - i - 1 for i in range(1, 57))
# sum2_comp = sum((64 - i) * 2 for i in range(57, 64))
# sum3_comp = sum((64 - i) * 2 for i in range(1, 64))
# numerator_comp = sum1_comp + sum2_comp
# denominator_comp = sum3_comp
# result_comp = numerator_comp / denominator_comp if denominator_comp != 0 else "Error"
# print(f"\nResult using comprehensions: {result_comp}")