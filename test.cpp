#include <cstdint>
#include <iostream>

static const uint16_t BIT_NUM = 64;
static const uint64_t SYMBOL_VALUE = 0x8000000000000000;
constexpr uint8_t LUA_FIXED_BP = 20;
constexpr uint64_t INTEGER_BITS = ((~0ULL >> LUA_FIXED_BP) << LUA_FIXED_BP);
constexpr uint64_t DECIMAL_BITS = ~INTEGER_BITS;
static const uint32_t LUA_FIXED_EPSILON = 0x00001000;
constexpr int64_t LUA_MAX_FIXEDPOINT_VALUE = (1ULL << (((64 - 1 - LUA_FIXED_BP) >> 1) + LUA_FIXED_BP)) - 1;
constexpr int64_t LUA_MIN_FIXEDPOINT_VALUE = -(1LL << (((64 - 1 - LUA_FIXED_BP) >> 1) + LUA_FIXED_BP));
constexpr int DEC_NUM_LEN = 1000;

//-----------------------------------------------------------------longlonglonglonglong bits number------------------------------------------------
static void left_move_bit(uint32_t* gb, int move_bit_num) {
	uint32_t head_bit = 0x80000000;
	uint32_t signal = gb[0] & head_bit;
	uint32_t tail_bit = 0x00000001;
	for (int j = 0; j < move_bit_num; j++) {
		for (int i = 0; i < BIT_NUM - 1; i++) {
			gb[i] <<= 1;
			if (gb[i + 1] & head_bit) {
				gb[i] |= tail_bit;
			}
		}
		gb[BIT_NUM - 1] <<= 1;
		head_bit >>= 1;
		tail_bit <<= 1;
	}
	gb[0] &= 0x7fffffff;
	gb[0] |= signal;
}

static void right_move_bit(uint32_t* gb, int move_bit_num) {
	uint32_t head_bit = 0x80000000;
	uint32_t signal = gb[0] & head_bit;
	uint32_t tail_bit = 0x00000001;
	for (int j = 0; j < move_bit_num; j++) {
		for (int i = BIT_NUM - 1; i > 0; i--) {
			gb[i] >>= 1;
			if (gb[i - 1] & tail_bit) {
				gb[i] |= head_bit;
			}
		}
		gb[0] >>= 1;
		gb[0] |= signal;
		tail_bit >>= 1;
		head_bit <<= 1;
	}
}

static void xor_func(const uint32_t* fp1value, const uint32_t* fp2value, uint32_t* result) {
	for (int i = 0; i < BIT_NUM; i++) {
		result[i] = fp1value[i] ^ fp2value[i];
	}
}

static void and_func(const uint32_t* fp1value, const uint32_t* fp2value, uint32_t* result) {
	for (int i = 0; i < BIT_NUM; i++) {
		result[i] = fp1value[i] & fp2value[i];
	}
}

static void add_func(const uint32_t* fp1value, const uint32_t* fp2value, uint32_t* result) {
	uint32_t a[BIT_NUM], b[BIT_NUM];
	for (int i = 0; i < BIT_NUM; i++) {
		a[i] = fp1value[i];
		b[i] = fp2value[i];
	}
	int tag = 1;
	for (int i = 0; i < BIT_NUM; i++) {
		if (b[i] != 0) {
			tag = 1;
			break;
		}
	}
	while (tag == 1) {
		tag = 0;
		xor_func(a, b, result);
		and_func(a, b, b);
		left_move_bit(b, 1);
		for (int i = 0; i < BIT_NUM; i++) {
			a[i] = result[i];
		}
		for (int i = 0; i < BIT_NUM; i++) {
			if (b[i] != 0) {
				tag = 1;
				break;
			}
		}
	}
}

static void sub_func(const uint32_t* fp1value, const uint32_t* fp2value, uint32_t* result) {
	uint32_t neg_b[BIT_NUM];
	uint32_t one[BIT_NUM] = { 0 };
	one[BIT_NUM - 1] = 1;
	for (int i = 0; i < BIT_NUM; i++) {
		neg_b[i] = (~fp2value[i]);
	}
	add_func(neg_b, one, neg_b);
	add_func(fp1value, neg_b, result);
}

static void mul_func(const uint32_t* fp1value, const uint32_t* fp2value, uint32_t* result) {
	uint32_t a[BIT_NUM], b[BIT_NUM];
	for (int i = 0; i < BIT_NUM; i++) {
		a[i] = fp1value[i];
		b[i] = fp2value[i];
	}
	int tag = 1;
	for (int i = 0; i < BIT_NUM; i++) {
		if (b[i] != 0) {
			tag = 1;
			break;
		}
	}
	while (tag == 1) {
		if ((b[BIT_NUM - 1] & static_cast<uint32_t>(1)) != 0) {
			add_func(a, result, result);
			left_move_bit(a, 1);
			right_move_bit(b, 1);
		}
		for (int i = 0; i < BIT_NUM; i++) {
			if (b[i] != 0) {
				tag = 1;
				break;
			}
		}
	}
}

static void div_func() {

}

static void getGB(uint32_t* gb, const char* str) {

}

static void getDecArrayWithBitsWithIndex(uint8_t* dec_num, int bits, int index, int& dec_bit_num) {
	int exp = 0;
	uint8_t ten = 10;
	if (index == 0) {
		dec_num[0] += 1;
		++exp;
		if (exp > dec_bit_num) {
			dec_bit_num = exp;
		}
	}
	for (int j = index; j > 0; j--) {
		uint64_t base_num = static_cast<uint64_t>(1) << bits;
		exp = 0;
		while (base_num) {
			dec_num[exp] += (base_num % ten);
			int carryBitCount = 0;
			while (dec_num[exp + carryBitCount] >= ten) {
				dec_num[exp + carryBitCount] -= ten;
				if ((exp + carryBitCount + 1) < DEC_NUM_LEN) {
					dec_num[exp + carryBitCount + 1] += 1;
					++carryBitCount;
					if (exp + carryBitCount + 1 > dec_bit_num) {
						dec_bit_num = exp + carryBitCount + 1;
					}
				}
				else {
					printf("dec number over MAX bits");
					break;
				}
			}
			++exp;
			base_num /= ten;
		}
		if (exp > dec_bit_num) {
			dec_bit_num = exp;
		}
	}
}

static void gbToDecString(char* result, const uint32_t* gb, int& dec_bit_num) {
	uint32_t temp[BIT_NUM];
	for (int i = 0; i < BIT_NUM; i++) {
		temp[i] = gb[i];
	}
	uint8_t neg = 0;
	uint32_t head_bit = 0x80000000;
	if (temp[0] & head_bit) {
		neg = 1;
		uint32_t one[BIT_NUM] = { 0 };
		one[BIT_NUM - 1] = 1;
		for (int i = 0; i < BIT_NUM; i++) {
			temp[i] = (~temp[i]);
		}
		add_func(temp, one, temp);
	}
	uint8_t dec_num[DEC_NUM_LEN] = { 0 };	//dec number array
	for (int i = 0; i < BIT_NUM; i++) {
		if (!temp[i]) {
			continue;
		}
		getDecArrayWithBitsWithIndex(dec_num, 32, BIT_NUM - i - 1, dec_bit_num);
	}
	for (int i = 0; i < dec_bit_num; i++) {
		result[i] = 48 + dec_num[i];
	}
	if (neg == 1) {
		result[dec_bit_num++] = '-';
	}
}

//-----------------------------------------------------------------64bits number-----------------------------------------------------------------
typedef struct {
	uint8_t signal;
	uint64_t integer;
	uint16_t decimals;
} SelfDefineNumber;

static SelfDefineNumber* add_function(const SelfDefineNumber a, const SelfDefineNumber b) {
	SelfDefineNumber* result = new SelfDefineNumber();
	uint8_t aBit = 0;
	uint8_t bBit = 0;
	for (int i = 0; i < 64; i++) {
		if (((1ULL << i) - 1) < a.integer && a.integer < ((1ULL << (i + 1)) - 1)) {
			aBit = i;
		}
		if (((1ULL << i) - 1) < b.integer && b.integer < ((1ULL << (i + 1)) - 1)) {
			bBit = i;
		}
	}
	if (a.signal == b.signal) {
		if (aBit >= 63 && bBit >= 63) {
			printf("¡¾Error¡¿a %llu b %llu add overflow\n", a.integer, b.integer);
		}
		else {
			result->signal = a.signal;
			result->integer = a.integer + b.integer;
			result->decimals = a.decimals + b.decimals;
		}
	}
	else {
		if (a.integer > b.integer) {
			result->signal = a.signal;
			result->integer = a.integer - b.integer;
			if (a.decimals > b.decimals) {
				result->decimals = a.decimals - b.decimals;
			}
			else if (a.decimals < b.decimals) {
				--result->integer;
				result->decimals = b.decimals - a.decimals;
				result->decimals = ((1UL << 16) - (result->decimals));
			}
			else {
				result->decimals = 0;
			}
		}
		else if (a.integer < b.integer) {
			result->signal = b.signal;
			result->integer = b.integer - a.integer;
			if (a.decimals > b.decimals) {
				--result->integer;
				result->decimals = a.decimals - b.decimals;
				result->decimals = ((1UL << 16) - (result->decimals));
			}
			else if (a.decimals < b.decimals) {
				result->decimals = b.decimals - a.decimals;
			}
			else {
				result->decimals = 0;
			}
		}
		else {
			result->integer = 0;
			if (a.decimals > b.decimals) {
				result->signal = a.signal;
				result->decimals = a.decimals - b.decimals;
			}
			else if (a.decimals < b.decimals) {
				result->signal = b.signal;
				result->decimals = b.decimals - a.decimals;
			}
			else {
				result->signal = 0;
				result->decimals = 0;
			}
		}
	}
	return result;
}
static SelfDefineNumber* sub_function(const SelfDefineNumber a, const SelfDefineNumber b) {
	SelfDefineNumber c;
	if (b.signal == 1) {
		c.signal = 0;
	}
	else if (b.signal == 0) {
		c.signal = 1;
	}
	c.integer = b.integer;
	c.decimals = b.decimals;
	return add_function(a, c);
}

static SelfDefineNumber* multi_function(const SelfDefineNumber a, const SelfDefineNumber b) {
	SelfDefineNumber* result = new SelfDefineNumber();
	uint8_t aBit = 0;
	uint8_t bBit = 0;
	for (int i = 0; i < 64; i++) {
		if (((1ULL << i) - 1) < a.integer && a.integer < ((1ULL << (i + 1)) - 1)) {
			aBit = i;
		}
		if (((1ULL << i) - 1) < b.integer && b.integer < ((1ULL << (i + 1)) - 1)) {
			bBit = i;
		}
	}
	if (a.signal != b.signal) {
		result->signal = 1;
	}
	else {
		result->signal = 0;
	}
	if (aBit + bBit >= 64) {
		printf("¡¾Error¡¿a %llu b %llu multi overflow\n", a.integer, b.integer);
	}
	else {
		result->integer = a.integer * b.integer;
	}
	return result;
}

static SelfDefineNumber* divi_function(const SelfDefineNumber a, const SelfDefineNumber b) {
	SelfDefineNumber* result = new SelfDefineNumber();
	if (a.signal != b.signal) {
		result->signal = 1;
	}
	else {
		result->signal = 0;
	}
	result->integer = a.integer / b.integer;
	uint64_t residue = (a.integer - b.integer * result->integer);
	result->decimals = residue;
	return result;
}

static void PrintSelfDefineNumber(SelfDefineNumber r) {
	if (r.signal == 1) {
		double decimals = r.decimals / (double)(1ULL << 16);
		printf("-%llu.%lf\n", r.integer, decimals);
	}
	else {
		double decimals = r.decimals / (double)(1ULL << 16);
		printf("%llu.%lf\n", r.integer, decimals);
	}
}

//-----------------------------------------------------------------fixedpoint number-----------------------------------------------------------------
static inline int64_t getG(const char* str)
{
	int64_t intenger = 0;
	int64_t fraction = 0;
	int64_t exp = 1;
	bool neg = false;

	if (*str != '\0' && *str == '-') {
		str++;
		neg = true;
	}

	for (; *str != '\0' && (*str >= '0' && *str <= '9'); str++) {
		int d = *str - '0';
		intenger = intenger * 10 + d;
	}

	if (*str == '.') {
		str++;
		int fractionNumberCount = 0;
		int maxFractionNumberCount = 6;
		for (; (fractionNumberCount < maxFractionNumberCount) && *str != '\0' && (*str >= '0' && *str <= '9'); str++) {
			int d = *str - '0';
			fraction = fraction * 10 + d;
			exp = exp * 10;
			++fractionNumberCount;
		}
	}

	int64_t result = (intenger << LUA_FIXED_BP) + ((fraction << LUA_FIXED_BP) / exp);

	if (neg) {
		result = -result;
	}

	return result;
}

#define LUA_FIXED_POINT_PI		getG("3.14159265359")

static inline int64_t math_floor(int64_t a) {
	int64_t result = 0;
	result = ((a >> LUA_FIXED_BP) << LUA_FIXED_BP);
	return result;
}

static inline int64_t math_ceil(int64_t a) {
	int64_t result = 0;
	if ((a & DECIMAL_BITS) == 0) {
		result = a;
	}
	else {
		result = (((a & INTEGER_BITS) + (1ULL << LUA_FIXED_BP)));
	}
	return result;
}

static void op_tonumber(int64_t a)
{
	if ((a & DECIMAL_BITS) == 0) {
		long long number = a >> LUA_FIXED_BP;
		printf("longlong number %I64d\n", number);
	}
	else {
		double number = a / (double)(1ULL << LUA_FIXED_BP);
		printf("double number %f\n", number);
	}
}

static int64_t sq(int64_t n) {
	return (((n - (long long)((unsigned long long)n & (~((1ULL << LUA_FIXED_BP) - 1)))) * n) >> LUA_FIXED_BP) + ((n >> LUA_FIXED_BP) * n);
}

static int64_t sqrt(int64_t n) {
	long long m, root = 0, left = n << LUA_FIXED_BP;
	for (m = 1LL << ((sizeof(long long) << 3) - 2); m; m >>= 2)
	{
		if ((left & -m) > root)
			left -= (root += m), root += m;
		root >>= 1;
	}
	return root;
}

static int64_t math_abs(int64_t v)
{
	int64_t result = v;
	if (v < getG("0")) {
		result = -v;
	}
	else {
		result = v;
	}
	return result;
}

static inline int64_t multiple_for_int64(int64_t fp1value, int64_t fp2value)
{
	if (fp1value > LUA_MAX_FIXEDPOINT_VALUE) {
		printf("incorrect argument 1. operand overflow MAX");
	}
	if (fp2value > LUA_MAX_FIXEDPOINT_VALUE) {
		printf("incorrect argument 2. operand overflow MAX");
	}

	return (((fp1value - (long long)((unsigned long long)fp1value & (~((1ULL << LUA_FIXED_BP) - 1)))) * fp2value) >> LUA_FIXED_BP) + ((fp1value >> LUA_FIXED_BP) * fp2value);
}

static inline int64_t divide_for_int64(int64_t fp1value, int64_t fp2value)
{
	if (fp1value < LUA_MIN_FIXEDPOINT_VALUE) {
		printf("incorrect argument 1. operand overflow MIN");
	}
	if (fp2value < LUA_MIN_FIXEDPOINT_VALUE) {
		printf("incorrect argument 2. operand overflow MIN");
	}

	return (fp1value << LUA_FIXED_BP) / (fp2value | 0x1);
}

static inline int64_t add_for_int64(int64_t fp1value, int64_t fp2value)
{
	if (fp1value > LUA_MAX_FIXEDPOINT_VALUE) {
		printf("incorrect argument 1. operand overflow MAX");
	}
	if (fp2value > LUA_MAX_FIXEDPOINT_VALUE) {
		printf("incorrect argument 2. operand overflow MAX");
	}

	return fp1value + fp2value;
}

static inline int64_t sub_for_int64(int64_t fp1value, int64_t fp2value)
{
	if (fp1value < LUA_MIN_FIXEDPOINT_VALUE) {
		printf("incorrect argument 1. operand overflow MIN");
	}
	if (fp2value < LUA_MIN_FIXEDPOINT_VALUE) {
		printf("incorrect argument 2. operand overflow MIN");
	}

	return fp1value - fp2value;
}

static int64_t math_atan(int64_t y, int64_t x)
{

	int64_t abs_y = (math_abs(y) + LUA_FIXED_EPSILON);	// avoid 0/0
	int64_t r, angle;

	if (x >= getG("0")) {
		r = divide_for_int64((x - abs_y), (x + abs_y));
		angle = divide_for_int64(LUA_FIXED_POINT_PI, getG("4"));
	}
	else {
		r = divide_for_int64((x + abs_y), (abs_y - x));
		angle = divide_for_int64(multiple_for_int64(getG("3"), LUA_FIXED_POINT_PI), getG("4"));
	}
	angle += multiple_for_int64(getG("0.1963"), multiple_for_int64(multiple_for_int64(r, r), r)) - multiple_for_int64(getG("0.9817"), r);
	int64_t result = (y < getG("0")) ? -angle : angle;
	return result;
}

static int64_t math_degree(int64_t rad)
{
	return multiple_for_int64(divide_for_int64(getG("180"), LUA_FIXED_POINT_PI), rad);
}

static inline void print(int64_t a) {
	//printf("%I64d\n", a);
	printf("%.6f\n", a / (double)(1ULL << LUA_FIXED_BP));
}

int getFixedpointIntegerBits(int64_t g) {
	int bits = 0;
	uint64_t ug = g;
	if (g < 0) {
		ug = -g;
	}
	ug = ug >> LUA_FIXED_BP << LUA_FIXED_BP;
	if (ug == 0) {
		return 0;
	}
	if (ug & 0xffffffff00000000) {
		ug >>= 32;
		bits += 32;
	}
	if (ug & 0xffff0000) {
		ug >>= 16;
		bits += 16;
	}
	if (ug & 0xff00) {
		ug >>= 8;
		bits += 8;
	}
	if (ug & 0xf0) {
		ug >>= 4;
		bits += 4;
	}
	if (ug & 0xc) {
		ug >>= 2;
		bits += 2;
	}
	if (ug & 0x2) {
		ug >>= 1;
		bits += 1;
	}
	if (ug & 0x1) {
		ug >>= 1;
		bits += 1;
	}
	return bits - LUA_FIXED_BP;
}

int test_main() {
	int64_t result = getG("10000");
	print(result);
	print(math_floor(result));
	print(math_ceil(result));
	op_tonumber(32768);
	op_tonumber(3276815);
	op_tonumber(1048576);
	print(sq(result));
	print(sqrt(result));
	print(math_abs(getG("-0.64050292")));
	print(math_abs(getG("-0.7678222")));
	print(math_atan(getG("-0.64050292"), getG("-0.7678222")));
	print(math_degree(getG("-2.4463548")));
	printf("----------------------\n");
	uint32_t example[BIT_NUM] = {0};
	example[BIT_NUM - 1] = 0x000000ff;
	example[BIT_NUM - 2] = 0x000000ff;
	example[BIT_NUM - 3] = 0x000000ff;
	example[BIT_NUM - 4] = 0x000000ff;
	char anumber[DEC_NUM_LEN] = { '0' };
	int dec_bit_num = 0;
	gbToDecString(anumber, example, dec_bit_num);
	printf("dec_bit_num : %d\n", dec_bit_num);
	for (int i = dec_bit_num; i >= 0; i--) {
		printf("%c", anumber[i]);
	}
	printf("\n--------------------------\n");
	SelfDefineNumber a;
	a.signal = 0;
	a.integer = 1ULL << 10;
	a.decimals = 3;
	SelfDefineNumber b;
	b.signal = 1;
	b.integer = 1ULL << 12;
	b.decimals = 2;
	printf("a: ");
	PrintSelfDefineNumber(a);
	printf("b: ");
	PrintSelfDefineNumber(b);
	printf("a+b: ");
	PrintSelfDefineNumber(*(add_function(a,b)));
	printf("a-b: ");
	PrintSelfDefineNumber(*(sub_function(a, b)));
	printf("a*b: ");
	PrintSelfDefineNumber(*(multi_function(a, b)));
	printf("a/b: ");
	PrintSelfDefineNumber(*(divi_function(a, b)));
	result = (1ULL << 63) + (1ULL << 25) + (1ULL << 14);
	printf("1 %llx %d\n", result, getFixedpointIntegerBits(result));
	result = (1ULL << 62) + (1ULL << 25) + (1ULL << 14);
	printf("2 %llx %d\n", result, getFixedpointIntegerBits(result));
	result = (1ULL << 61) + (1ULL << 25) + (1ULL << 14);
	printf("3 %llx %d\n", result, getFixedpointIntegerBits(result));
	result = (1ULL << 60) + (1ULL << 25) + (1ULL << 14);
	printf("4 %llx %d\n", result, getFixedpointIntegerBits(result));
	result = (1ULL << 59) + (1ULL << 25) + (1ULL << 14);
	printf("5 %llx %d\n", result, getFixedpointIntegerBits(result));
	result = (1ULL << 58) + (1ULL << 25) + (1ULL << 14);
	printf("6 %llx %d\n", result, getFixedpointIntegerBits(result));
	result = (1ULL << 57) + (1ULL << 25) + (1ULL << 14);
	printf("7 %llx %d\n", result, getFixedpointIntegerBits(result));
	result = (1ULL << 56) + (1ULL << 25) + (1ULL << 14);
	printf("8 %llx %d\n", result, getFixedpointIntegerBits(result));
	result = (1ULL << 55) + (1ULL << 25) + (1ULL << 14);
	printf("9 %llx %d\n", result, getFixedpointIntegerBits(result));
	result = (1ULL << 54) + (1ULL << 10) + (1ULL << 1);
	printf("10 %llx %d\n", result, getFixedpointIntegerBits(result));
	result = (1ULL << 53) + (1ULL << 10) + (1ULL << 1);
	printf("11 %llx %d\n", result, getFixedpointIntegerBits(result));
	result = (1ULL << 52) + (1ULL << 10) + (1ULL << 1);
	printf("12 %llx %d\n", result, getFixedpointIntegerBits(result));
	result = (1ULL << 51) + (1ULL << 10) + (1ULL << 1);
	printf("13 %llx %d\n", result, getFixedpointIntegerBits(result));
	result = (1ULL << 50) + (1ULL << 1) + (1ULL << 1);
	printf("14 %llx %d\n", result, getFixedpointIntegerBits(result));
	result = (1ULL << 49) + (1ULL << 1) + (1ULL << 1);
	printf("15 %llx %d\n", result, getFixedpointIntegerBits(result));
	result = (1ULL << 48) + (1ULL << 1) + (1ULL << 1);
	printf("16 %llx %d\n", result, getFixedpointIntegerBits(result));
	result = (1ULL << 47) + (1ULL << 1) + (1ULL << 1);
	printf("17 %llx %d\n", result, getFixedpointIntegerBits(result));
	result = (1ULL << 46) + (1ULL << 1) + (1ULL << 1);
	printf("18 %llx %d\n", result, getFixedpointIntegerBits(result));
	result = (1ULL << 45) + (1ULL << 1) + (1ULL << 1);
	printf("19 %llx %d\n", result, getFixedpointIntegerBits(result));
	result = (1ULL << 44) + (1ULL << 1) + (1ULL << 1);
	printf("20 %llx %d\n", result, getFixedpointIntegerBits(result));
	result = (1ULL << 43) + (1ULL << 1) + (1ULL << 1);
	printf("21 %llx %d\n", result, getFixedpointIntegerBits(result));
	result = (1ULL << 42) + (1ULL << 1) + (1ULL << 1);
	printf("22 %llx %d\n", result, getFixedpointIntegerBits(result));
	result = (1ULL << 41) + (1ULL << 1) + (1ULL << 1);
	printf("23 %llx %d\n", result, getFixedpointIntegerBits(result));
	result = (1ULL << 40) + (1ULL << 1) + (1ULL << 1);
	printf("24 %llx %d\n", result, getFixedpointIntegerBits(result));
	result = (1ULL << 39) + (1ULL << 1) + (1ULL << 1);
	printf("17 %llx %d\n", result, getFixedpointIntegerBits(result));
	result = (1ULL << 38) + (1ULL << 1) + (1ULL << 1);
	printf("18 %llx %d\n", result, getFixedpointIntegerBits(result));
	result = (1ULL << 37) + (1ULL << 1) + (1ULL << 1);
	printf("19 %llx %d\n", result, getFixedpointIntegerBits(result));
	result = (1ULL << 36) + (1ULL << 1) + (1ULL << 1);
	printf("20 %llx %d\n", result, getFixedpointIntegerBits(result));
	result = (1ULL << 35) + (1ULL << 1) + (1ULL << 1);
	printf("21 %llx %d\n", result, getFixedpointIntegerBits(result));
	result = (1ULL << 34) + (1ULL << 1) + (1ULL << 1);
	printf("22 %llx %d\n", result, getFixedpointIntegerBits(result));
	result = (1ULL << 33) + (1ULL << 1) + (1ULL << 1);
	printf("23 %llx %d\n", result, getFixedpointIntegerBits(result));
	result = (1ULL << 32) + (1ULL << 1) + (1ULL << 1);
	printf("24 %llx %d\n", result, getFixedpointIntegerBits(result));
	result = (1ULL << 31) + (1ULL << 1) + (1ULL << 1);
	printf("23 %llx %d\n", result, getFixedpointIntegerBits(result));
	result = (1ULL << 30) + (1ULL << 1) + (1ULL << 1);
	printf("24 %llx %d\n", result, getFixedpointIntegerBits(result));
	result = ~0ULL;
	printf("24 %llx %d\n", result, getFixedpointIntegerBits(result));
	result = ~0ULL >> 1;
	printf("24 %llx %d\n", result, getFixedpointIntegerBits(result));
	result = 1;
	printf("24 %llx %d\n", result, getFixedpointIntegerBits(result));
	return 0;
}