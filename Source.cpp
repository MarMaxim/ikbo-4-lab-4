#include "stdlib.h"
#include "stdio.h"
#include "fann.h"
#include "floatfann.h"
#include <iostream>

using std::cout;
using std::endl;

int main(int argc,char **argv){
	int i;
	const unsigned int num_input = 3; //���������� ������� ��������
	const unsigned int num_output = 1; //���������� �������� ��������
	const unsigned int num_layers = 3; //���������� ����� ��������� ����
	const unsigned int num_neurons_hidden = 3; //���������� �������� � ������� ����
	const float desired_error = (const float) 0.01; //��������
	const unsigned int max_epochs = 1000; //���������� ������ ��������(��� �������� ����)
	fann_type *calc_out; //�������� ������
	fann_type input[3]; //������� �������

	// �������� ��������� ���� � ������ ann
	struct fann *ann = fann_create_standard(num_layers, num_input,num_neurons_hidden, num_output);

	fann_set_activation_function_hidden(ann, FANN_SIGMOID_SYMMETRIC);
	fann_set_activation_function_output(ann, FANN_SIGMOID_SYMMETRIC);

	//��������
	//fann_train_on_file(ann, "training.txt", max_epochs,10, desired_error);

	//�������� ��������� ��������� ����
	ann = fann_create_from_file("func.net");
	
	//������� �������� ������� ��������
	for (i = 0; i < 3; i++)
		if (argv[i + 1][0] == '0')
			input[i] = 0;
		else
			input[i] = 1;

	//������� �������� ��������� �������
	calc_out = fann_run(ann, input);

	//����� ����������� c ��������� �������
	printf("%f\n", calc_out[0]);
	if (calc_out[0] > 0.5)
		printf("%d", 1);
	else
		printf("%d", 0);

	//���������� ��������� ���� � ����
	//fann_save(ann, "func.net");
	
	//������� ���������
	fann_destroy(ann);
	
	return 0;
}