char *report(short m, short n, char *p)
{
    int result;
    char *temp;
    long nm;
    int i, k, kk;
    char name[11] = "Joe Jakeso";
    nm = n * m;
    temp = p == "" ? (char*)"null" : p;
    for (i = 0; i < m; i++)
    {
        k++;
        kk = i;
    }
    if (k == 1)
        result = nm;
    else if (kk > 0)
        result = 1;
    else if (kk < 0)
        result = -1;
    if (m == result)
        return temp;
    else
        return name;
}
