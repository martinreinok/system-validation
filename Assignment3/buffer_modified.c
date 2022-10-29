/*
 * Modified from:
 * Copyright (c) 2020 Siddharth Chandrasekaran <siddharth@embedjournal.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

int* buffer;
int head = 0;
int tail = 0;
int const maxlen = 4;

/*@
assigns tail, *output_arr;
*/
int pop(int *output_arr) {
	int next;
	if (head == tail)
		return -1; // buffer is empty
	next = tail + 1;
	if (next >= maxlen)
		next = 0;
	*output_arr = buffer[tail];
	tail = next;
	return 0;
}

/*@
assigns head, buffer[head];

behavior good:
	requires (head + 1 < maxlen && head + 1 != tail) || (head + 1 >= maxlen && tail != 0);
	ensures head == \old(head) + 1;
	ensures \result == 0;

behavior reset_buffer:
	requires head + 1 >= maxlen && tail != 0;
	ensures head == 0;
	ensures \result == 0;

behavior bad:
	requires (head + 1 < maxlen && head + 1 == tail) || (head + 1 >= maxlen && 0 == tail);
	ensures \result == -1;

complete behaviors;
disjoint behaviors;
*/
int push(int data) {
	int next;
	next = head + 1;
	if (next >= maxlen)
		next = 0;
	if (next == tail)
		return -1; // buffer is full
	buffer[head] = data;
	head = next;
	return 0;
}

/*@ assigns buffer; */
int main() {
	int data[4];
	buffer = data;
	int out[4];
	int a = 1;
	int b = 1;
	push(a);
	push(b);

	/*@ loop assigns i, a, b; */
	for (int i = 2; i < maxlen-1; i++) {
		int sum = a + b;
		if(push(sum)) {
			// Out of space
			return -1;
		}
		a = b;
		b = sum;
	}

	return 0;
}
