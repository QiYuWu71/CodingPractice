def series18(n):
    """Your code goes here."""
    result = [-n**2]
    ele = -n **2
    for i in range(1,3*n):
        ele = ele+2*i-1
        result.append(ele)
    return result

series18(1)
series18(5)
series18(7)
series18(12)
