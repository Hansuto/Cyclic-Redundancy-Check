// Christopher Taliaferro
// Ch119541 || 4199356

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#define polyLen strlen(poly)

char bin[100], hex[20], CRC[100], poly[] = "1100110110101", *binPtr;
int binLen, i = 0, j, k, y, x = 0;

// Performs XOR Operation
void xor()
{
	for (k = 1; k < polyLen; k++)
		CRC[k] = ((CRC[k] == poly[k]) ? '0' : '1');
}

// CRC Function
void crc()
{
	for (j = 0; j < polyLen; j++)
		CRC[j] = bin[j];

	do
	{
		if (CRC[0] == '1')
			xor ();

		for (k = 0; k < (polyLen - 1); k++)
			CRC[k] = CRC[k + 1];

		CRC[k] = bin[j++];
		printf("\nThe intermediate result is: %s", CRC);

	} while (j <= binLen + polyLen - 1);
}

// Converts HEX values into Binary Representation
void hex2bin()
{
	while (hex[i])
	{
		switch (tolower(hex[i]))
		{
		case '0':
			strcat(bin, "0000"); break;
		case '1':
			strcat(bin, "0001"); break;
		case '2':
			strcat(bin, "0010"); break;
		case '3':
			strcat(bin, "0011"); break;
		case '4':
			strcat(bin, "0100"); break;
		case '5':
			strcat(bin, "0101"); break;
		case '6':
			strcat(bin, "0110"); break;
		case '7':
			strcat(bin, "0111"); break;
		case '8':
			strcat(bin, "1000"); break;
		case '9':
			strcat(bin, "1001"); break;
		case 'a':
			strcat(bin, "1010"); break;
		case 'b':
			strcat(bin, "1011"); break;
		case 'c':
			strcat(bin, "1100"); break;
		case 'd':
			strcat(bin, "1101"); break;
		case 'e':
			strcat(bin, "1110"); break;
		case 'f':
			strcat(bin, "1111"); break;
		default:
			printf("\n Invalid hex digit %c ", hex[i]);
			exit(1);
		}
		i++;
	}
}

// Converts Binary into HEX Representation
void bin2hex()
{
	binPtr = bin;
	do {
		y = *binPtr == '1' ? 1 : 0;
		x = (x << 1) | y;
		binPtr++;
	} while (*binPtr);
}

// Verifies CRC contains nothing but '0'
void crcVerify()
{
	for (j = 0; (j < (polyLen - 1)) && (CRC[j] != '1'); j++);
	if (j < polyLen - 1) printf("\nVerification failed\n");
	else printf("\nVerification is successful!\n");
}

// Pads Binary message with (polynomial - 1) zeros
void padding()
{
	binLen = strlen(bin);
	for (j = binLen; j<binLen + polyLen - 1; j++)
		bin[j] = '0';
}

// Attaches the CRC to the Binary input message 
void finalAppendage()
{
	for (j = binLen; j < binLen + polyLen - 1; j++)
        bin[j] = CRC[j - binLen];
}

// Validates that HEX value entered is of proper length
void hexVerify()
{
    if (strlen(hex) < 3 || strlen(hex) > 5)
    {
        printf("ERROR : Hex value must be of length 3, 4, or 5");
        exit(1);
    }
}

int main()
{
	printf("Enter input message in Hex: ");
	scanf("%s", hex);
	hexVerify();
	hex2bin();

	printf("\nInput message in binary is: %s", bin);
	printf("\nThe polynomial in binary: %s", poly);
	padding();

	printf("\nModified message is : %s", bin);
	printf("\nThe initial data is:\t    %s", bin);
	crc();

	printf("\nThe CRC is : %s", CRC);
	finalAppendage();

	printf("\nFinal appended message is: %s", bin);
	bin2hex();

	printf("\nFinal appended message in HEX is: %X", x);
	printf("\nStart the verification process...\n");

    // Clear data from 'bin'
	i = 0;
	memset(bin, 0, 26);

	printf("Enter input message in Hex: ");
	scanf("%s", hex);
	hex2bin();

	printf("\nThe message in binary is: %s", bin);
	printf("\nThe initial data is:\t    %s", bin);

	crc();
	crcVerify();

	return 0;
}
