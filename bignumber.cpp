#include "bignumber.h"

BigNumber::BigNumber(const string&str1, NumbSystem system)
{
    if(str1.size() == 0) return;

    switch(system)
    {
        case NumbSystem::DEC:
        {
            int len = str1.length();
            count_num = 0;

            if(len > 0)
            {
                count_num = len;
                pNumber = new numType[count_num];
                for(int iii = 0; iii<count_num; iii++)
                {
                    pNumber[iii] = str1[count_num - iii - 1] - 48;
                }
            }
        }
        break;

        case NumbSystem::BIN:
        {
            BigNumber num_res;
            BigNumber num_res1;

            int off1 = 0;

			for(int iii = str1.length() - 1; iii >= 0; --iii)
			{
				int ddd = 0;

				ddd = str1[iii] - 48;

				if(ddd == 1)
				{
					BigNumber num_2("2");
					num_res1 = num_2^off1;
					num_res += num_res1;

				}
				off1++;
			}

            *this = num_res;
        }
        break;

        case NumbSystem::HEX:
        {
            BigNumber num_res;
            BigNumber num_res1;

            int off1 = 0;

			for(int iii = str1.length() - 1; iii >= 2; iii--)
			{
				char ch1 = str1[iii];
				int ddd = 0;

				if (('a' <= ch1) && (ch1 <= 'f'))
				{
					ddd = 10 + str1[iii] - 97;
				}
				else
				{
					ddd = str1[iii] - 48;
				}
				if(ddd > 0)
				{
					BigNumber num_res3;
					BigNumber num_res2(ddd);
					BigNumber num_16((char *)"16");

					num_res1 = num_16^off1;
					num_res3 = num_res2 * num_res1;
					num_res +=  num_res3;
				}
				off1++;
			}
			*this = num_res;
		}
		break;

	}
}

BigNumber::BigNumber(int numb)
{
    //char str1[256];
    //str1[0] = 0;
    //sprintf(str1, "%d", numb);
    string str1 = std::to_string(numb);

    count_num = static_cast<int>(str1.size());
    pNumber = new numType[count_num];

    for(int iii = 0; iii<count_num; iii++)
    {
        char ch1 = str1[count_num - iii - 1] - 48;
        pNumber[iii] = ch1;
    }
}

BigNumber::BigNumber(const BigNumber&v1)
{
    count_num = v1.count_num;
    pNumber = new numType[count_num];
    for(int iii = 0; iii < count_num; iii++)
    {
        pNumber[iii] = v1.pNumber[iii];
    }
}

BigNumber::BigNumber(int*b1, int c)
{
    this->count_num = c;
    pNumber = new numType[count_num];
    for(int iii = 0; iii < this->count_num; iii++)
    {
        pNumber[iii] = b1[iii];
    }
}

BigNumber::~BigNumber()
{
    delete []pNumber;
}


void BigNumber::setData(numType*ptr, int len)
{
    this->count_num = len;

    if(pNumber)
    {
        delete []pNumber;
    }

    pNumber = nullptr;

    if(len > 0)
    {
        pNumber = new numType[count_num];
        for(int iii = 0; iii < this->count_num; iii++)
        {
            pNumber[iii] = ptr[iii];
        }
    }
}

void BigNumber::setString(char *str1)
{
    //printf("string this=%p count=%d\n", this, count);
    int iii;
    if(!str1) return;

    //printf("count=%d\n", this->count);
    for(iii = 0; iii<this->count_num; iii++)
    {
        char ch1 = static_cast<char>(pNumber[this->count_num - iii - 1] + 48);
        //printf("ch1=%c \n", ch1);
        *(str1 + iii) = ch1;
    }

    *(str1 + iii) = 0;
}

string BigNumber::getDecString() const
{
    string strDec;
    strDec.reserve(count_num);

    for(int iii = 0; iii<count_num; iii++)
    {
        strDec += static_cast<char>(pNumber[this->count_num - iii - 1] + 48);
    }

    return strDec;
}

string BigNumber::getBinString() const
{
    int ost = 0;
    BigNumber num1 = {*this};
    BigNumber num2;
    string      strBin;

    strBin.reserve(this->count_num * 4);

    for(;;)
    {
        num2 = num1/2;
        ost = num1%2;

        if(ost)
        {
            strBin += "1";
        }
        else
        {
            strBin += "0";
        }

        if(num2.size() == 0)
        {
            break;
        }
        num1 = num2;
    }
    strBin += "b";

    std::reverse(strBin.begin(), strBin.end());

    return strBin;
}

string BigNumber::getHexString() const
{
	int ost = 0;

	BigNumber num1 = {*this};
	BigNumber num2;

    string strHex;
    strHex.reserve(this->count_num + 2);


	for(;;)
	{
		char str2[8];
		num2	= num1/16;
		ost		= num1%16;

		if(ost > 9)
		{
			char str1[] = {'a', 'b', 'c', 'd', 'e', 'f'};
			sprintf(str2, "%c", str1[ost - 10]);
		}
		else
		{
			sprintf(str2, "%d", ost);
		}

		strHex += str2;

		if(num2.size() == 0)
		{
			break;
		}
		num1 = num2;
	}
	strHex += "x0";
	std::reverse(strHex.begin(), strHex.end());

	return strHex;
}

//Перегрузка операции вывода в поток
ostream& operator << (ostream &s, const BigNumber &b)
{
    if(b.count_num == 0)
    {
        s << "0";
        return s;
    }

    switch(b.printFormat)
    {
        case BigNumber::NumbSystem::DEC:
        {
            s << b.getDecString();
        }
        break;

        case BigNumber::NumbSystem::BIN:
        {
            s << b.getBinString();
        }
        break;

        case BigNumber::NumbSystem::HEX:
        {                        
            s << b.getHexString();
        }
        break;
    }
    return s;
}

void BigNumber::print() const
{
    //printf("print this=%p count=%d\n", this, count);

    for(int iii = 0; iii<count_num; iii++)
    {
        printf("%d", pNumber[count_num - iii - 1]);
    }
    printf("\n");
}

BigNumber& BigNumber::operator*(BigNumber const &v1)
{
    int len;
    numType *arr1;

    len = v1.count_num + this->count_num + 1;
    arr1 = new numType[len];

    for(int iii=0; iii<len; iii++)
    {
        arr1[iii] = 0;
    }


    for(int ix=0; ix < this->count_num; ix++)
    {
        for(int jx=0; jx < v1.count_num; jx++)
        {
            arr1[ix + jx] += this->pNumber[ix]*v1.pNumber[jx];
        }
    }

    for(int iii=0; iii<len; iii++)
    {
        arr1[iii + 1] += arr1[iii]/10;
        arr1[iii] %= 10;
    }

    //printf("len=%d arr1[len-1]=%d\n", len, arr1[len]);
    while(arr1[len-1] == 0)
    {
        len--;
        //printf("len=%d arr1[len]=%d\n", len, arr1[len]);
    }

    this->setData(arr1, len);
    delete []arr1;

    return *this;
}

BigNumber& BigNumber::operator = (BigNumber const &v1)
{
	if(this != &v1)
	{
		this->count_num = v1.count_num;
		
		if(this->pNumber)
		{
			delete []this->pNumber;
		}
		
		this->pNumber = new numType[this->count_num];
		
		for(int iii = 0; iii < count_num; iii++)
		{
			this->pNumber[iii] = v1.pNumber[iii];
		}
	}
	return *this;
}

BigNumber operator / (BigNumber const &v1, int const &n)
{
    int len;
    BigNumber::numType *arr1;
    int osn = 10;
    int ost =0;

    BigNumber result;
    len = v1.count_num;
    arr1 = new BigNumber::numType[len];

    for(int iii=0; iii<len; iii++)
    {
        arr1[iii] = 0;
    }
    for(int iii = len - 1; iii >= 0; iii--)
    {
        int cur = ost*osn + v1.pNumber[iii];
        arr1[iii] = cur/n;
        ost = cur % n;
    }
    while(arr1[len-1] == 0)
    {
        len--;
    }

    if(len < 0)
    {
        len = 0;
    }

    //cout << "delenie len=" << len<< endl;
    result.setData(arr1, len);
    delete []arr1;
    return result;
}

int operator%(BigNumber const &v1, int const &n)
{
    int len;
    BigNumber::numType *arr1;
    int osn = 10;
    int ost =0;

    BigNumber result;
    len = v1.count_num;
    arr1 = new BigNumber::numType[len];

    for(int iii=0; iii<len; iii++)
    {
        arr1[iii] = 0;
    }
    for(int iii = len - 1; iii >= 0; iii--)
    {
        int cur = ost*osn + v1.pNumber[iii];
        arr1[iii] = cur/n;
        ost = cur % n;
    }
    while(arr1[len-1] == 0)
    {
        len--;
    }
    result.setData(arr1, len);
    delete []arr1;

    return ost;
}

BigNumber  operator + (BigNumber const &v1, BigNumber const &v2)
{
    BigNumber temp = v1;
    return temp += v2;
}

BigNumber& BigNumber::operator^(int range)
{
    BigNumber *aaa = nullptr;
    BigNumber *bbb = nullptr;

    if(range == 0)
    {
        aaa = new BigNumber("1");
        this->setData(aaa->pNumber, aaa->count_num);
    }
    else
        if(range == 1)
        {
        }
        else
        {
            //printf("range=%d\n", range);
            for(int iii=0; iii<(range-1); iii++)
            {
                if(aaa)
                {
                    delete aaa;
                }
                else
                {
                    bbb = new BigNumber(*this);
                }

                aaa = new BigNumber((*bbb) * (*this));
                delete bbb;
                bbb = new BigNumber(*aaa);
                //bbb->print();
            }
            //printf("end loop\n");
            this->setData(aaa->pNumber, aaa->count_num);
        }

    return *this;
}

const BigNumber &BigNumber::operator ++()
{
    return *this += 1;
}

const BigNumber BigNumber::operator ++(int)
{
    BigNumber temp = *this;
    *this += 1;
    return temp;
}

const BigNumber& BigNumber::operator += (const BigNumber&v1)
{
    BigNumber &v2 = *this;

    int len = 0;
    BigNumber::numType *arr1;
    BigNumber::numType *arr2;

    if(v2.count_num > v1.count_num)
    {
        len = v2.count_num + 1;
    }
    else
    {
        len = v1.count_num + 1;
    }

    arr1 = new BigNumber::numType[len];
    arr2 = new BigNumber::numType[len];

    for(int iii=0; iii<len; ++iii)
    {
        arr1[iii] = 0;
        arr2[iii] = 0;
    }

    for(int iii=0; iii<v2.count_num; ++iii)
    {
        arr1[iii] = v2.pNumber[iii];
    }
    for(int iii=0; iii<v1.count_num; ++iii)
    {
        arr2[iii] = v1.pNumber[iii];
    }
    for(int ix=0; ix<len; ix++)
    {
        arr1[ix] += arr2[ix];
        arr1[ix + 1] += (arr1[ix]/10);
        arr1[ix] %= 10;
    }

    if(arr1[len - 1] == 0)
    {
        --len;
    }

    setData(arr1, len);

    delete []arr1;
    delete []arr2;

    return *this;
}

void BigNumber::setPrintFormat(const NumbSystem& value)
{
    printFormat = value;
}

bool operator !=(const BigNumber &v1, const BigNumber &v2)
{
    return !(v1 == v2);
}

bool operator >=(const BigNumber &v1, const BigNumber &v2)
{
    return !(v1 < v2);
}

bool operator <=(const BigNumber &v1, const BigNumber &v2)
{
    return !(v1 > v2);
}

bool operator ==(const BigNumber &v1, const BigNumber &v2)
{
    return !(v1 < v2 || v1 > v2);
}

bool operator <(const BigNumber &v1, const BigNumber &v2)
{
    bool result = false;
    if(v1.count_num == v2.count_num)
    {
        int len = v1.count_num - 1;
        while(len >= 0)
        {
            if(v1.pNumber[len] != v2.pNumber[len])
            {
                result = v1.pNumber[len] < v2.pNumber[len];
                break;
            }
            --len;
        }
    }
    else
    if(v1.count_num < v2.count_num)
    {
        result = true;
    }
    return result;
}

bool operator > (const BigNumber &v1, const BigNumber &v2)
{
    return v2 < v1;
}
