// 2013013017 ���ſ�
// ����Ÿ��� ���� 2 - 2) CheckSum

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 1000

// 16���� ���ڿ�, ���� ��ȯ�ϱ�
int hexToInt(char hex);
char intToHex(int data);
void intToBin(int, int, int);
void binToComp(int);
void checksum(int,int);

// data
char send[MAX], recv[MAX];
char bin[MAX][MAX]; // ������ ��ȯ
char compBin[MAX][MAX]; // ������ ���� ��ȯ
int B[MAX];				// ������ ����
int compB[MAX];			// ���������� ����
char sumBin[MAX];		// SUM bin
char CsumBin[MAX];		// CSUM bin
int checksumInt[4];		// checksumInt

void main() {

	int input;
	int n = 0, i;
	int data;
	int sum = 0, csum = 0;

	// ��� str
	char str1[] = "1: �۽�";
	char str2[] = "2: ����";
	char str3[] = "3: Exit";

	// �޼��� ���
	char str4[] = "�۽� �޼���(16����) �Է�:";
	char str5[] = "���� �޼���(16����) �Է�:";
	char str6[] = "<2���� ��ȯ>";

	// ���� ����
	// ��� ȭ��
	printf("%s\n%s\n%s\n", str1, str2, str3);
	printf("> ");

	// ���� ����
	fflush(stdin);

	// �Է� �ޱ�
	scanf("%d", &input);

	// �ɼ� ����
	switch (input) {
		// �۽�
		case 1:
			// 16���� �Է¹ޱ�
			printf("%s", str4);
			scanf("%s", send);

			// 16���� -> ����
			// i�� 4���� üũ (16 ��Ʈ)
			for (i = 0; i < strlen(send); i += 4) {
				for (int j = i; j < i + 4; j++) {
					data = hexToInt(send[j]);
					intToBin(n, 4 * (j - i), data); // bin ���ڿ��� �� �ֱ�
				}
				n++; // ���� word
			}

			// 2���� ��ȯ
			printf("%s\n", str6);
			
			// ���� �� 
			for (i = 0; i < strlen(send) / 4; i++) {
				printf("%s\n", bin[i]);
				B[i] = (int)strtol(bin[i], NULL, 2); // �� ��ȯ �� ����
				sum += B[i]; // ����
			}

			// checkSum ó��
			checksum(sum,i);
			
			// sum ���
			printf("Sum: %s\n", sumBin);
			
			// checksum ���
			printf("Checksum: ");
			for (i = 0; i < 4; i++) {
				printf("%c ", intToHex(checksumInt[i]));
			}
			printf("\n");

			// �۽Ÿ޼��� ���
			printf("�۽� �� : ");
			for (i = 0; i < strlen(send); i++) {
				printf("%c", send[i]);
				if (i % 2 == 1)
					printf(" "); //2ĭ���� ĭ ����
			}

			printf("[");
			// checksum ���
			for (i = 0; i < 4; i++) {
				printf("%c", intToHex(checksumInt[i]));
				if (i == 1)
					printf(" "); //2ĭ���� ĭ ����
			}
			printf("]\n");
			break;

			// ����
		case 2:
			// 16���� �Է¹ޱ�
			printf("%s", str5);
			scanf("%s", recv);

			// 16���� -> ����
			// i�� 4���� üũ (16 ��Ʈ)
			for (i = 0; i < strlen(recv); i += 4) {
				for (int j = i; j < i + 4; j++) {
					data = hexToInt(recv[j]);
					intToBin(n, 4 * (j - i), data); // bin ���ڿ��� �� �ֱ�
				}
				n++; // ���� word
			}

			// 2���� ��ȯ
			printf("%s\n", str6);

			// ���� �� 
			for (i = 0; i < strlen(recv) / 4; i++) {
				printf("%s\n", bin[i]);
				B[i] = (int)strtol(bin[i], NULL, 2); // �� ��ȯ �� ����
				sum += B[i]; // ����
			}

			// checkSum ó��
			checksum(sum, i);

			// sum ���
			printf("Sum: %s\n", sumBin);

			// Calculated checksum ���
			printf("Calculated Checksum: ");
			for (i = 0; i < 4; i++) {
				printf("%c ", intToHex(checksumInt[i]));
			}
			printf("\n");

			// ����üũ
			if (checksumInt[0] == 0 && checksumInt[1] == 0 && checksumInt[2] == 0 && checksumInt[3] == 0) {
				printf("���� ����\n");
			}
			else
				printf("���� ����\n");
			
			break;
			
			//exit
		case 3:
			return;
	}

}


// 16���� ���ڿ� -> ���� ��ȯ�ϱ�
int hexToInt(char hex) {

	// �� ��ȯ
	switch (hex) {
		
		// F 
		case 'f':
			return 15;

		// E
		case 'e':
			return 14;

		// D
		case 'd':
			return 13;

		// C
		case 'c':
			return 12;

		// B
		case 'b':
			return 11;

		// A
		case 'a':
			return 10;

		// 0~9
		default:
			return hex - '0';
	}

}

// ���� -> 16���� ���ڿ� ��ȯ�ϱ�
char intToHex(int data) {

	// �� ��ȯ
	switch (data) {

			// F 
		case 15:
			return 'F';

			// E
		case 14:
			return 'E';

			// D
		case 13:
			return 'D';

			// C
		case 12:
			return 'C';

			// B
		case 11:
			return 'B';

			// A
		case 10:
			return 'A';

			// 0~9
		default:
			return data+'0';
	}

}

// 16���� ->  ���� -> 4bit ������ �迭�� �ֱ�
void intToBin(int i, int j, int data) {
	// �� �ֱ�
	for (int cnt = 3; cnt >=0; cnt--) {
		bin[i][j+cnt] = (data % 2 )+ '0';
		data = data / 2;
	}
}

// ����
void binToComp(int i) {
	for (int j = 0; j < 16; j++) {
		if (bin[i][j] == '0')
			compBin[i][j] = '1';
		else
			compBin[i][j] = '0';
	}
}

// sum�� 2���� ���ڿ��� ��ȯ
void checksum(int sum, int n) {

	char binary[MAX];
	char buf[MAX];
	char buf2[MAX];
	char buf3[MAX];
	int data = sum;
	int i = 0;
	int cnt = 0;

	// data�� 0 �� �ƴҵ���
	while (data) {
		binary[i++] = data % 2 +'0'; // ���� ó��
		data = data / 2;
	}

	// ���ڿ�������
	for (int j = 0; j < i; j++) {
		buf[j] = binary[i-1-j];
	}

	// ���ڿ� (�������� carry �� ������ �����ֱ�)
	// buf 2 = 16�ڸ� sum
	for (int j = i - 16; j < i; j++) {
		buf2[cnt++] = buf[j];
	}
	buf2[cnt] = NULL;

	cnt = 0;
	// buf 3 = carry ��
	for (int j = 0; j < i - 16; j++) {
		buf3[cnt++] = buf[j];
	}
	buf3[cnt] = NULL;

	// �� ��������
	int data1 = (int)strtol(buf2, NULL, 2);
	int data2 = (int)strtol(buf3, NULL, 2);

	// �����ֱ�
	int data3 = data1 + data2;

	// data3 -> 2���� ��ȯ
	// data3�� 0 �� �ƴҵ���
	i = 0;
	while (data3) {
		binary[i++] = data3 % 2 + '0'; // ���� ó��
		data3 = data3 / 2;
	}

	// ���ڿ�������
	for (int j = 0; j < i; j++) {
		sumBin[j] = binary[i - 1 - j];
	}

	// ���� ���ϱ�
	for (int j = 0; j < 16; j++) {
		if (sumBin[j] == '0')
			CsumBin[j] = '1';
		else
			CsumBin[j] = '0';
	}

	// 4���� ���ڿ� �ڸ���
	int z = 0;
	cnt = 0;
	char csumBin[4][5];
	for (int k = 0; k < 16; k += 4) {
		for (int l = k; l < k + 4; l++) {
			csumBin[cnt][z++] = CsumBin[l];
		}
		cnt++; // ������
		csumBin[cnt][4] = NULL; // ���ڿ������
		z = 0; // �ʱ�ȭ
	}
	

	// �� ��ȯ �ϳ���
	for (i = 0; i < 4; i++) {
		checksumInt[i] = (int)strtol(csumBin[i], NULL, 2); // 2���� ��ȯ �ѱ��
	}
}