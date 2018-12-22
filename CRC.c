// 2013013017 ���ſ�
// ����Ÿ��� ���� 2 - 1) CRC

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAX 1000

// CRC �Լ�
void CRC(char*, char*);

// remainder
char fcs[MAX];

void main() {

	// ��� str
	char str1[] = "1: Dataword to codeword";
	char str2[] = "2: Codeword to dataword";
	char str3[] = "3: Exit";

	// �Է°�
	int input;
	char dataword[MAX],dataword2[MAX], divisor[MAX], codeword[MAX];
	int remainder[MAX];
	int size,cnt=0;
	unsigned long dw, dv, dw2, cw, rm;

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
		// dataword -> codeword
		case 1:
			//�Է¹ޱ�
			printf("Dataword : ");
			scanf("%s", dataword);

			printf("Divisor	 : ");
			scanf("%s", divisor);

			// Dataword2 �� �߰�
			strcpy(dataword2, dataword);
			for (int i = 0 ; i < strlen(divisor)-1; i++) {
				strcat(dataword2, "0");
			}

			// ��ȣȭ -> remainder�� ����
			CRC(dataword2, divisor);

			// Remainder ���
			printf("Remainder: ");

			// 0�� ������ʿ� x
			cnt = 0;
			while(fcs[cnt] == '0') {
				cnt++;
			}
			for (int i = cnt; i < strlen(fcs); i++)
				printf("%c", fcs[i]);
			printf("\n");
			
			// FCS ���
			printf("FCS      : ");
			printf("%s\n\n", fcs);

			// Codeword ���
			printf("Codeword : %s",dataword);
			printf("%s\n", fcs);

			break;

		// codeword -> dataword
		case 2:
			//�Է¹ޱ�
			printf("Codeword : ");
			scanf("%s", codeword);

			printf("Divisor	 : ");
			scanf("%s", divisor);

			// ��ȣȭ -> remainder�� ����
			CRC(codeword, divisor);

			// Remainder ���
			printf("Remainder: ");

			// 0�� ������ʿ� x
			cnt = 0;
			while (fcs[cnt] == '0') {
				cnt++;
			}
			for (int i = cnt; i < strlen(fcs); i++)
				printf("%c", fcs[i]);
			printf("\n");

			// FCS ���
			printf("FCS      : ");
			printf("%s\n\n", fcs);

			// ��ȿ�� üũ
			while (fcs[cnt] == '0') {
				cnt++;
			}

			// ��ȿ���
			if (cnt >= strlen(fcs)) {
				printf("��ȿ��!\n");
				printf("Dataword : ");
				for (int i = 0; i < strlen(codeword) - strlen(divisor)+1; i++)
					printf("%c", codeword[i]);
				printf("\n");
			}
			// ��ȿ���
			else {
				printf("��ȿ��!\n");
			}

			break;

		// exit
		case 3:
			return;
	}
}

// CRC
void CRC(char * word, char * div) {

	int i,idx=0, wordlen = strlen(word), divlen=strlen(div);
	int buf[MAX], buf2[MAX];

	// �ʱⰪ ��������
	for (int i = 0; i < strlen(div)-1; i++) {
		if (word[i] == '0')
			buf[i] = 0;
		else
			buf[i] = 1;
	}

	// ������ �ݺ��� ��������ŭ
	while (idx < ((wordlen - divlen)+1)) {
	
		//  ���� �ϳ� �߰�
		if (word[idx + divlen - 1] == '0')
			buf[divlen - 1] = 0;
		else
			buf[divlen - 1] = 1;

		// ù���ڰ� 0 
		if (buf[0] == 0) {
			
			// xor �����ϸ鼭 �� �߰�
			for (i = 1; i < divlen; i++) {
				buf2[i-1] = buf[i] ^ 0;
			}

			// buf2 -> buf�� �� �ű��
			for (i = 0; i < divlen -1; i++)
				buf[i] = buf2[i];

			// ���� idx ����
			idx++;
		}

		// ù���ڰ� 1
		else if (buf[0] == 1) {
			
			// xor �����ϸ鼭 �� �߰�
			for (i = 1; i < divlen; i++) {
				buf2[i-1] = buf[i] ^ (div[i]-'0');
			}

			// buf2 -> buf�� �� �ű��
			for (i = 0; i < divlen-1; i++)
				buf[i] = buf2[i];

			// ���� idx ����
			idx++;
		}
	}

	// ���� buf�� ���� remainder ���� ������
	for (i = 0; i < divlen - 1; i++) {
		fcs[i] = buf[i] + '0';
	}

}