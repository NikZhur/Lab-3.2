#include <iostream>
#include <string>

using namespace std;

struct Stack {
	string num;
	Stack* head;
	Stack* tail;
};

int operationPr(char perem) {
	switch (perem) {
	case '(':
		return 1;
	case ')':
		return 1;
	case '+':
		return 2;
	case '-':
		return 2;
	case '*':
		return 3;
	case '/':
		return 3;
	default:
		return 0;
	}
}


string lastElemnum(Stack* stack) {
	while (stack->tail != 0) {
		stack = stack->tail;
	}
	return stack->num;
}

Stack* lastElem(Stack* stack) {
	while (stack->tail != 0) {
		stack = stack->tail;
	}
	return stack;
}

int lastindStack(Stack* stack) {
	int k = 0;
	while (stack->tail != 0) {
		stack = stack->tail;
		k++;
	}
	return k;
}

Stack* reversPolnotation(string s) {
	Stack* res = 0;
	Stack* stack = 0;
	int len;
	len = s.length();
	int prior;

	for (int i = 0; i < len; i++) {
		if (s[i] == '(') {
			if (stack == 0) {
				Stack* item = new Stack;
				item->head = 0;
				item->tail = 0;
				item->num = s[i];
				stack = item;
			}
			else {
				Stack* item = new Stack;
				item->num = s[i];
				int lastIndex = lastindStack(stack);
				Stack* predItem = stack;
				while (predItem->tail && (lastIndex--)) {
					predItem = predItem->tail;
				}
				item->head = predItem;
				item->tail = predItem->tail;
				predItem->tail = item;
				if (item->tail != 0) {
					item->tail->head = item;
				}
			}
		}
		if (s[i] == ')') {
			string lastDop = lastElemnum(stack);
			char last = lastDop[0];
			int lastPrior = operationPr(last);
			while (lastPrior != 1) {
				Stack* newItem = new Stack;
				newItem->num = lastElemnum(stack);
				if (res == 0) {
					newItem->head = 0;
					newItem->tail = 0;
					res = newItem;
				}
				else {
					int lastIndex = lastindStack(res);
					Stack* predItem = res;
					while (predItem->tail && (lastIndex--)) {
						predItem = predItem->tail;
					}
					newItem->head = predItem;
					newItem->tail = predItem->tail;
					predItem->tail = newItem;
					if (newItem->tail != 0) {
						newItem->tail->head = newItem;
					}
				}

				cout << "выражение в скобках, переносим в итог  " << last << '\n';
				int ind = lastindStack(stack);
				Stack* item2;
				if (!ind) {
					item2 = stack->tail;
					delete stack;
					stack = item2;
					if (stack != 0) {
						stack->head = 0;
					}
					break;

				}
				item2 = stack;
				--ind;
				while (ind--) {
					item2 = item2->tail;
				}
				Stack* dItem = item2->tail;
				item2->tail = dItem->tail;
				if (item2->tail != 0) {
					item2->tail->head = item2;
				}
				delete dItem;
				lastDop = lastElemnum(stack);
				last = lastDop[0];
				lastPrior = operationPr(last);
			}
			int ind = lastindStack(stack);
			Stack* item2;
			if (!ind) {
				item2 = stack->tail;
				delete stack;
				stack = item2;
				if (stack != 0) {
					stack->head = 0;
				}
				break;

			}
			item2 = stack;
			--ind;
			while (ind--) {
				item2 = item2->tail;
			}
			Stack* dItem = item2->tail;
			item2->tail = dItem->tail;
			if (item2->tail != 0) {
				item2->tail->head = item2;
			}
			delete dItem;
		}
		if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/') {
			prior = operationPr(s[i]);
			if (stack == 0) {
				Stack* item = new Stack;
				item->head = 0;
				item->tail = 0;
				item->num = s[i];
				stack = item;
			}
			else if (stack != 0) {
				string lastDop = lastElemnum(stack);
				char last = lastDop[0];
				int lastPrior = operationPr(last);
				if (prior > lastPrior) {
					Stack* item = new Stack;
					item->num = s[i];
					int lastIndex = lastindStack(stack);
					Stack* predItem = stack;
					while (predItem->tail && (lastIndex--)) {
						predItem = predItem->tail;
					}
					item->head = predItem;
					item->tail = predItem->tail;
					predItem->tail = item;
					if (item->tail != 0) {
						item->tail->head = item;
					}
				}
				else {
					while (prior <= lastPrior) {
						Stack* newItem = new Stack;
						newItem->num = lastElemnum(stack);
						if (res == 0) {
							newItem->head = 0;
							newItem->tail = 0;
							res = newItem;
						}
						else {
							int lastIndex = lastindStack(res);
							Stack* predItem = res;
							while (predItem->tail && (lastIndex--)) {
								predItem = predItem->tail;
							}
							newItem->head = predItem;
							newItem->tail = predItem->tail;
							predItem->tail = newItem;
							if (newItem->tail != 0) {
								newItem->tail->head = newItem;
							}
						}

						cout << "Приоритет операции меньше или равен следующему, переносим в итог  " << last << '\n';
						int ind = lastindStack(stack);
						Stack* item2;
						if (!ind) {
							item2 = stack->tail;
							delete stack;
							stack = item2;
							if (stack != 0) {
								stack->head = 0;
							}
							break;

						}
						item2 = stack;
						--ind;
						while (ind--) {
							item2 = item2->tail;
						}
						Stack* dItem = item2->tail;
						item2->tail = dItem->tail;
						if (item2->tail != 0) {
							item2->tail->head = item2;
						}
						delete dItem;
						lastDop = lastElemnum(stack);
						last = lastDop[0];
						lastPrior = operationPr(last);
					}
					if (stack == 0) {
						Stack* item = new Stack;
						item->head = 0;
						item->tail = 0;
						item->num = s[i];
						stack = item;
					}
					else {
						Stack* item = new Stack;
						item->num = s[i];
						int lastIndex = lastindStack(stack);
						Stack* predItem = stack;
						while (predItem->tail && (lastIndex--)) {
							predItem = predItem->tail;
						}
						item->head = predItem;
						item->tail = predItem->tail;
						predItem->tail = item;
						if (item->tail != 0) {
							item->tail->head = item;
						}
					}
				}
			}
		}
		if ('0' <= s[i] && s[i] <= '9') {
			string perem = "";
			while ('0' <= s[i] && s[i] <= '9') {
				perem += s[i];
				i++;
			}
			i--;
			Stack* newItem = new Stack;
			newItem->num = perem;
			if (res == 0) {
				newItem->head = 0;
				newItem->tail = 0;
				res = newItem;
			}
			else {
				int lastIndex = lastindStack(res);
				Stack* predItem = res;
				while (predItem->tail && (lastIndex--)) {
					predItem = predItem->tail;
				}
				newItem->head = predItem;
				newItem->tail = predItem->tail;
				predItem->tail = newItem;
				if (newItem->tail != 0) {
					newItem->tail->head = newItem;
				}
			}

			cout << "Число, записываем в итог  " << perem << '\n';
		}
	}
	Stack* Lastel = lastElem(stack);
	while (Lastel != 0) {
		Stack* newItem = new Stack;
		newItem->num = Lastel->num;
		if (res == 0) {
			newItem->head = 0;
			newItem->tail = 0;
			res = newItem;
		}
		else {
			int lastIndex = lastindStack(res);
			Stack* predItem = res;
			while (predItem->tail && (lastIndex--)) {
				predItem = predItem->tail;
			}
			newItem->head = predItem;
			newItem->tail = predItem->tail;
			predItem->tail = newItem;
			if (newItem->tail != 0) {
				newItem->tail->head = newItem;
			}
		}

		cout << "Выводим стек  " << Lastel->num << '\n';
		Lastel = Lastel->head;
	}
	cout << "\n\n\n";
	cout << "Обратная польская нотация:  ";
	Stack* curr = res;
	while (curr)
	{
		cout << curr->num;
		curr = curr->tail;
	}
	cout << '\n';

	return res;
}

Stack* reversPolnotationDop(string s) {
	Stack* res = 0;
	Stack* stack = 0;
	int len;
	len = s.length();
	int prior;

	for (int i = 0; i < len; i++) {
		if (s[i] == '(') {
			if (stack == 0) {
				Stack* item = new Stack;
				item->head = 0;
				item->tail = 0;
				item->num = s[i];
				stack = item;
			}
			else {
				Stack* item = new Stack;
				item->num = s[i];
				int lastIndex = lastindStack(stack);
				Stack* predItem = stack;
				while (predItem->tail && (lastIndex--)) {
					predItem = predItem->tail;
				}
				item->head = predItem;
				item->tail = predItem->tail;
				predItem->tail = item;
				if (item->tail != 0) {
					item->tail->head = item;
				}
			}
		}
		if (s[i] == ')') {
			string lastDop = lastElemnum(stack);
			char last = lastDop[0];
			int lastPrior = operationPr(last);
			while (lastPrior != 1) {
				Stack* newItem = new Stack;
				newItem->num = lastElemnum(stack);
				if (res == 0) {
					newItem->head = 0;
					newItem->tail = 0;
					res = newItem;
				}
				else {
					int lastIndex = lastindStack(res);
					Stack* predItem = res;
					while (predItem->tail && (lastIndex--)) {
						predItem = predItem->tail;
					}
					newItem->head = predItem;
					newItem->tail = predItem->tail;
					predItem->tail = newItem;
					if (newItem->tail != 0) {
						newItem->tail->head = newItem;
					}
				}

				int ind = lastindStack(stack);
				Stack* item2;
				if (!ind) {
					item2 = stack->tail;
					delete stack;
					stack = item2;
					if (stack != 0) {
						stack->head = 0;
					}
					break;

				}
				item2 = stack;
				--ind;
				while (ind--) {
					item2 = item2->tail;
				}
				Stack* dItem = item2->tail;
				item2->tail = dItem->tail;
				if (item2->tail != 0) {
					item2->tail->head = item2;
				}
				delete dItem;
				lastDop = lastElemnum(stack);
				last = lastDop[0];
				lastPrior = operationPr(last);
			}
			int ind = lastindStack(stack);
			Stack* item2;
			if (!ind) {
				item2 = stack->tail;
				delete stack;
				stack = item2;
				if (stack != 0) {
					stack->head = 0;
				}
				break;

			}
			item2 = stack;
			--ind;
			while (ind--) {
				item2 = item2->tail;
			}
			Stack* dItem = item2->tail;
			item2->tail = dItem->tail;
			if (item2->tail != 0) {
				item2->tail->head = item2;
			}
			delete dItem;
		}
		if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/') {
			prior = operationPr(s[i]);
			if (stack == 0) {
				Stack* item = new Stack;
				item->head = 0;
				item->tail = 0;
				item->num = s[i];
				stack = item;
			}
			else if (stack != 0) {
				string lastDop = lastElemnum(stack);
				char last = lastDop[0];
				int lastPrior = operationPr(last);
				if (prior > lastPrior) {
					Stack* item = new Stack;
					item->num = s[i];
					int lastIndex = lastindStack(stack);
					Stack* predItem = stack;
					while (predItem->tail && (lastIndex--)) {
						predItem = predItem->tail;
					}
					item->head = predItem;
					item->tail = predItem->tail;
					predItem->tail = item;
					if (item->tail != 0) {
						item->tail->head = item;
					}
				}
				else {
					while (prior <= lastPrior) {
						Stack* newItem = new Stack;
						newItem->num = lastElemnum(stack);
						if (res == 0) {
							newItem->head = 0;
							newItem->tail = 0;
							res = newItem;
						}
						else {
							int lastIndex = lastindStack(res);
							Stack* predItem = res;
							while (predItem->tail && (lastIndex--)) {
								predItem = predItem->tail;
							}
							newItem->head = predItem;
							newItem->tail = predItem->tail;
							predItem->tail = newItem;
							if (newItem->tail != 0) {
								newItem->tail->head = newItem;
							}
						}

						int ind = lastindStack(stack);
						Stack* item2;
						if (!ind) {
							item2 = stack->tail;
							delete stack;
							stack = item2;
							if (stack != 0) {
								stack->head = 0;
							}
							break;

						}
						item2 = stack;
						--ind;
						while (ind--) {
							item2 = item2->tail;
						}
						Stack* dItem = item2->tail;
						item2->tail = dItem->tail;
						if (item2->tail != 0) {
							item2->tail->head = item2;
						}
						delete dItem;
						lastDop = lastElemnum(stack);
						last = lastDop[0];
						lastPrior = operationPr(last);
					}
					if (stack == 0) {
						Stack* item = new Stack;
						item->head = 0;
						item->tail = 0;
						item->num = s[i];
						stack = item;
					}
					else {
						Stack* item = new Stack;
						item->num = s[i];
						int lastIndex = lastindStack(stack);
						Stack* predItem = stack;
						while (predItem->tail && (lastIndex--)) {
							predItem = predItem->tail;
						}
						item->head = predItem;
						item->tail = predItem->tail;
						predItem->tail = item;
						if (item->tail != 0) {
							item->tail->head = item;
						}
					}
				}
			}
		}
		if ('0' <= s[i] && s[i] <= '9') {
			string perem = "";
			while ('0' <= s[i] && s[i] <= '9') {
				perem += s[i];
				i++;
			}
			i--;
			Stack* newItem = new Stack;
			newItem->num = perem;
			if (res == 0) {
				newItem->head = 0;
				newItem->tail = 0;
				res = newItem;
			}
			else {
				int lastIndex = lastindStack(res);
				Stack* predItem = res;
				while (predItem->tail && (lastIndex--)) {
					predItem = predItem->tail;
				}
				newItem->head = predItem;
				newItem->tail = predItem->tail;
				predItem->tail = newItem;
				if (newItem->tail != 0) {
					newItem->tail->head = newItem;
				}
			}

		}
	}
	Stack* Lastel = lastElem(stack);
	while (Lastel != 0) {
		Stack* newItem = new Stack;
		newItem->num = Lastel->num;
		if (res == 0) {
			newItem->head = 0;
			newItem->tail = 0;
			res = newItem;
		}
		else {
			int lastIndex = lastindStack(res);
			Stack* predItem = res;
			while (predItem->tail && (lastIndex--)) {
				predItem = predItem->tail;
			}
			newItem->head = predItem;
			newItem->tail = predItem->tail;
			predItem->tail = newItem;
			if (newItem->tail != 0) {
				newItem->tail->head = newItem;
			}
		}

		Lastel = Lastel->head;
	}
	cout << "\n\n\n";
	cout << "Обратная польская нотация:  ";
	Stack* curr = res;
	while (curr)
	{
		cout << curr->num;
		curr = curr->tail;
	}
	cout << '\n';

	return res;
}


Stack* Polnotation(string s) {
	Stack* res = 0;
	Stack* stack = 0;
	int len;
	len = s.length();
	int prior;

	for (int i = len - 1; i >= 0; i--) {
		if (s[i] == ')') {
			if (stack == 0) {
				Stack* item = new Stack;
				item->head = 0;
				item->tail = 0;
				item->num = s[i];
				stack = item;
			}
			else {
				Stack* item = new Stack;
				item->num = s[i];
				item->head = 0;
				item->tail = stack;
				stack->head = item;
				stack = item;
			}
		}
		if (s[i] == '(') {
			string startDop = stack->num;
			char start = startDop[0];
			int startPrior = operationPr(start);
			while (startPrior != 1) {
				Stack* newItem = new Stack;
				newItem->num = stack->num;
				if (res == 0) {
					newItem->head = 0;
					newItem->tail = 0;
					res = newItem;
				}
				else {
					newItem->head = 0;
					newItem->tail = res;
					res->head = newItem;
					res = newItem;
				}

				cout << "выражение в скобках, переносим в итог  " << start << '\n';
				int ind = 0;
				Stack* item2;
				if (!ind) {
					item2 = stack->tail;
					delete stack;
					stack = item2;
					if (stack != 0) {
						stack->head = 0;
					}

				}
				startDop = stack->num;
				start = startDop[0];
				startPrior = operationPr(start);
			}
			int ind = 0;
			Stack* item2;
			if (!ind) {
				item2 = stack->tail;
				delete stack;
				stack = item2;
				if (stack != 0) {
					stack->head = 0;
				}

			}

		}
		if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/') {
			prior = operationPr(s[i]);
			if (stack == 0) {
				Stack* item = new Stack;
				item->head = 0;
				item->tail = 0;
				item->num = s[i];
				stack = item;
			}
			else if (stack != 0) {
				string startDop = stack->num;
				char start = startDop[0];
				int startPrior = operationPr(start);
				if (prior >= startPrior) {
					Stack* item = new Stack;
					item->num = s[i];
					item->head = 0;
					item->tail = stack;
					stack->head = item;
					stack = item;
				}
				else {
					while (prior < startPrior) {
						Stack* newItem = new Stack;
						newItem->num = stack->num;
						if (res == 0) {
							newItem->head = 0;
							newItem->tail = 0;
							res = newItem;
						}
						else {
							newItem->head = 0;
							newItem->tail = res;
							res->head = newItem;
							res = newItem;
						}

						cout << "Приоритет операции меньше следующего, переносим в итог  " << start << '\n';
						int ind = 0;
						Stack* item2;
						if (!ind) {
							item2 = stack->tail;
							delete stack;
							stack = item2;
							if (stack != 0) {
								stack->head = 0;
							}
						}
						if (stack != 0) {
							startDop = stack->num;
							start = startDop[0];
							startPrior = operationPr(start);
						}
						else {
							break;
						}

					}
					if (stack == 0) {
						Stack* item = new Stack;
						item->head = 0;
						item->tail = 0;
						item->num = s[i];
						stack = item;
					}
					else {

						Stack* item = new Stack;
						item->num = s[i];
						item->head = 0;
						item->tail = stack;
						stack->head = item;
						stack = item;
					}
				}
			}
		}

		if ('0' <= s[i] && s[i] <= '9') {
			string perem = "";
			while (i >= 0 && '0' <= s[i] && s[i] <= '9') {
				perem = s[i] + perem;
				i--;
			}
			i++;
			Stack* newItem = new Stack;
			newItem->num = perem;
			if (res == 0) {
				newItem->head = 0;
				newItem->tail = 0;
				res = newItem;
			}
			else {
				newItem->head = 0;
				newItem->tail = res;
				res->head = newItem;
				res = newItem;
			}

			cout << "Число, записываем в итог с конца " << perem << '\n';
		}
	}
	Stack* First = stack;
	while (First != 0) {
		Stack* newItem = new Stack;
		newItem->num = First->num;
		if (res == 0) {
			newItem->head = 0;
			newItem->tail = 0;
			res = newItem;
		}
		else {
			newItem->head = 0;
			newItem->tail = res;
			res->head = newItem;
			res = newItem;
		}

		cout << "Выводим стек  " << First->num << '\n';
		First = First->tail;
	}
	cout << "\n\n\n";
	cout << "Польская нотация:  ";
	Stack* curr = res;
	while (curr)
	{
		cout << curr->num;
		curr = curr->tail;
	}
	cout << '\n';

	return res;
}



Stack* PolnotationDop(string s) {
	Stack* res = 0;
	Stack* stack = 0;
	int len;
	len = s.length();
	int prior;

	for (int i = len - 1; i >= 0; i--) {
		if (s[i] == ')') {
			if (stack == 0) {
				Stack* item = new Stack;
				item->head = 0;
				item->tail = 0;
				item->num = s[i];
				stack = item;
			}
			else {
				Stack* item = new Stack;
				item->num = s[i];
				item->head = 0;
				item->tail = stack;
				stack->head = item;
				stack = item;
			}
		}
		if (s[i] == '(') {
			string startDop = stack->num;
			char start = startDop[0];
			int startPrior = operationPr(start);
			while (startPrior != 1) {
				Stack* newItem = new Stack;
				newItem->num = stack->num;
				if (res == 0) {
					newItem->head = 0;
					newItem->tail = 0;
					res = newItem;
				}
				else {
					newItem->head = 0;
					newItem->tail = res;
					res->head = newItem;
					res = newItem;
				}

				int ind = 0;
				Stack* item2;
				if (!ind) {
					item2 = stack->tail;
					delete stack;
					stack = item2;
					if (stack != 0) {
						stack->head = 0;
					}

				}
				startDop = stack->num;
				start = startDop[0];
				startPrior = operationPr(start);
			}
			int ind = 0;
			Stack* item2;
			if (!ind) {
				item2 = stack->tail;
				delete stack;
				stack = item2;
				if (stack != 0) {
					stack->head = 0;
				}

			}

		}
		if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/') {
			prior = operationPr(s[i]);
			if (stack == 0) {
				Stack* item = new Stack;
				item->head = 0;
				item->tail = 0;
				item->num = s[i];
				stack = item;
			}
			else if (stack != 0) {
				string startDop = stack->num;
				char start = startDop[0];
				int startPrior = operationPr(start);
				if (prior >= startPrior) {
					Stack* item = new Stack;
					item->num = s[i];
					item->head = 0;
					item->tail = stack;
					stack->head = item;
					stack = item;
				}
				else {
					while (prior < startPrior) {
						Stack* newItem = new Stack;
						newItem->num = stack->num;
						if (res == 0) {
							newItem->head = 0;
							newItem->tail = 0;
							res = newItem;
						}
						else {
							newItem->head = 0;
							newItem->tail = res;
							res->head = newItem;
							res = newItem;
						}

						int ind = 0;
						Stack* item2;
						if (!ind) {
							item2 = stack->tail;
							delete stack;
							stack = item2;
							if (stack != 0) {
								stack->head = 0;
							}
						}
						if (stack != 0) {
							startDop = stack->num;
							start = startDop[0];
							startPrior = operationPr(start);
						}
						else {
							break;
						}

					}
					if (stack == 0) {
						Stack* item = new Stack;
						item->head = 0;
						item->tail = 0;
						item->num = s[i];
						stack = item;
					}
					else {

						Stack* item = new Stack;
						item->num = s[i];
						item->head = 0;
						item->tail = stack;
						stack->head = item;
						stack = item;
					}
				}
			}
		}

		if ('0' <= s[i] && s[i] <= '9') {
			string perem = "";
			while (i >= 0 && '0' <= s[i] && s[i] <= '9') {
				perem = s[i] + perem;
				i--;
			}
			i++;
			Stack* newItem = new Stack;
			newItem->num = perem;
			if (res == 0) {
				newItem->head = 0;
				newItem->tail = 0;
				res = newItem;
			}
			else {
				newItem->head = 0;
				newItem->tail = res;
				res->head = newItem;
				res = newItem;
			}

		}
	}
	Stack* First = stack;
	while (First != 0) {
		Stack* newItem = new Stack;
		newItem->num = First->num;
		if (res == 0) {
			newItem->head = 0;
			newItem->tail = 0;
			res = newItem;
		}
		else {
			newItem->head = 0;
			newItem->tail = res;
			res->head = newItem;
			res = newItem;
		}

		First = First->tail;
	}
	cout << "\n\n\n";
	cout << "Польская нотация:  ";
	Stack* curr = res;
	while (curr)
	{
		cout << curr->num;
		curr = curr->tail;
	}
	cout << '\n';

	return res;
}


void corectPolnotation(Stack* res, string s) {
	string prov = "";
	Stack* curr = res;
	while (curr)
	{
		prov += curr->num;
		curr = curr->tail;
	}
	if (s == prov) {
		cout << "Ваша польская нотация правильная\n\n";
	}
	else {
		cout << "Ваша польская нотация неправильная\n\n";
/*		cout << "Правильная польская нотация:  ";
		curr = res;
		while (curr)
		{
			cout << curr->num;
			curr = curr->tail;
		}
		cout << "\n\n";*/
	}
}


void corectreversPolnotation(Stack* res, string s) {
	string prov = "";
	Stack* curr = res;
	while (curr)
	{
		prov += curr->num;
		curr = curr->tail;
	}
	if (s == prov) {
		cout << "Ваша обратная польская нотация правильная\n\n";
	}
	else {
		cout << "Ваша обратная польская нотация неправильная\n\n";
/*		cout << "Правильная обратная польская нотация:  ";
		curr = res;
		while (curr)
		{
			cout << curr->num;
			curr = curr->tail;
		}
		cout << "\n\n";*/
	}
}


bool corectExpression(string s) {
	int len;
	len = s.length();
	bool flag = true;
	if (s[0] == ')' || s[0] == '+' || s[0] == '-' || s[0] == '*' || s[0] == '/') {
		flag = false;
	}
	if (s[len - 1] == '(' || s[len - 1] == '+' || s[len - 1] == '-' || s[len - 1] == '*' || s[len - 1] == '/') {
		flag = false;
	}
	for (int i = 0; i < len - 1; i++) {
		if ((s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/') && (s[i + 1] == '+' || s[i + 1] == '-' || s[i + 1] == '*' || s[i + 1] == '/')) {
			flag = false;
		}
		if (s[i] == '/' && s[i + 1] == '0') {
			flag = false;
		}
		if ((s[i] == '(' && s[i + 1] == ')') || (s[i] == ')' && s[i + 1] == '(')) {
			flag = false;
		}
		if (('0' <= s[i] && s[i] <= '9' && s[i + 1] == '(') || (s[i] == ')' && '0' <= s[i + 1] && s[i + 1] <= '9')) {
			flag = false;
		}
	}
	int count1 = 0;
	int count2 = 0;
	for (int i = 0; i < len; i++) {
		if (s[i] == '(') {
			count1++;
		}
		if (s[i] == ')') {
			count2++;
		}
	}
	if (count1 != count2) {
		flag = false;
	}
	return flag;
}

void inPerem(string& s) {
	int len;
	len = s.length();
	string init = "";
	string prom = "";
	int lenProm;
	bool flag;
	for (int i = 0; i < len; i++) {
		if (s[i] == ' ') {
			continue;
		}
		if ('a' <= s[i] && s[i] <= 'z' || 'A' <= s[i] && s[i] <= 'Z') {
			flag = false;
			lenProm = prom.length();
			for (int j = 0; j < lenProm; j++) {
				if (s[i] == prom[j]) {
					flag = true;
					j++;
					while (!('a' <= prom[j] && prom[j] <= 'z' || 'A' <= prom[j] && prom[j] <= 'Z') && prom[j]) {
						init += prom[j];
						j++;
					}
					j--;
					break;
				}
			}
			if (!flag) {
				cout << "Инициализируйте переменную  " << s[i] << "\n";
				string in;
				cin >> in;
				init += in;
				prom += s[i];
				prom += in;
			}

		}
		else {
			init += s[i];
		}
	}
	s = init;
}


int resultEx(int perem1, int perem2, char s) {
	int res = 0;
	switch (s) {
	case '+':
		res = perem1 + perem2;
		break;
	case '-':
		res = perem1 - perem2;
		break;
	case '*':
		res = perem1 * perem2;
		break;
	case '/':
		res = perem1 / perem2;
		break;
	}
	return res;
}

int resRevPolnotation(Stack* res) {
	int result = 0;
	int dop;
	Stack* perem = 0;
	Stack* curr = res;
	string s;
	string s2;
	bool flag;
	while (curr)
	{
		flag = false;
		if (curr->num == "+" || curr->num == "-" || curr->num == "*" || curr->num == "/") {
			flag = true;
			s = curr->head->num;
			int lens;
			lens = s.length();;
			int perem = 0;
			int temp = 1;
			for (int j = lens - 1; j >= 0; j--) {
				if (s[j] == '-') {
					perem = -perem;
					break;
				}
				perem += (s[j] - '0') * temp;
				temp *= 10;
			}
			s2 = curr->head->head->num;
			int lens2;
			lens2 = s2.length();;
			int perem2 = 0;
			int temp2 = 1;
			for (int j = lens2 - 1; j >= 0; j--) {
				if (s2[j] == '-') {
					perem2 = -perem2;
					break;
				}
				perem2 += (s2[j] - '0') * temp2;
				temp2 *= 10;
			}
			dop = resultEx(perem2, perem, curr->num[0]);
			cout << '\n' << perem2 << curr->num << perem << "=" << dop;

			curr->head->head->num = to_string(dop);

			Stack* item;
			item = curr->head->head;

			curr = curr->tail;
			for (int i = 0; i < 2; i++) {
				Stack* dItem = item->tail;
				item->tail = dItem->tail;
				if (item->tail != 0) {
					item->tail->head = item;
				}
				delete dItem;
			}
		}
		if (!flag) {
			curr = curr->tail;
		}
	}
	s = res->num;
	int lens;
	lens = s.length();;
	int nums = 0;
	int temp = 1;
	for (int j = lens - 1; j >= 0; j--) {
		if (s[j] == '-') {
			nums = -nums;
			break;
		}
		nums += (s[j] - '0') * temp;
		temp *= 10;
	}
	result = nums;
	return result;
}


int resPolnotation(Stack* res) {
	int result = 0;
	int dop;
	Stack* perem = 0;
	Stack* curr = res;
	while (curr->tail != 0) {
		curr = curr->tail;
	}
	string s;
	string s2;
	bool flag;
	while (curr)
	{
		flag = false;
		if (curr->num == "+" || curr->num == "-" || curr->num == "*" || curr->num == "/") {
			flag = true;
			s = curr->tail->num;
			int lens;
			lens = s.length();;
			int perem = 0;
			int temp = 1;
			for (int j = lens - 1; j >= 0; j--) {
				if (s[j] == '-') {
					perem = -perem;
					break;
				}
				perem += (s[j] - '0') * temp;
				temp *= 10;
			}
			s2 = curr->tail->tail->num;
			int lens2;
			lens2 = s2.length();;
			int perem2 = 0;
			int temp2 = 1;
			for (int j = lens2 - 1; j >= 0; j--) {
				if (s2[j] == '-') {
					perem2 = -perem2;
					break;
				}
				perem2 += (s2[j] - '0') * temp2;
				temp2 *= 10;
			}
			dop = resultEx(perem, perem2, curr->num[0]);
			cout << '\n' << perem << curr->num << perem2 << "=" << dop;

			curr->tail->tail->num = to_string(dop);

			Stack* item;
			item = curr->tail->tail;
			if (curr->head == 0) {
				res = curr->tail->tail;
			}
			curr = curr->head;
			for (int i = 0; i < 2; i++) {
				Stack* dItem = item->head;
				item->head = dItem->head;
				if (item->head != 0) {
					item->head->tail = item;
				}
				delete dItem;
			}
		}
		if (!flag) {
			curr = curr->head;
		}
	}
	s = res->num;
	int lens;
	lens = s.length();;
	int nums = 0;
	int temp = 1;
	for (int j = lens - 1; j >= 0; j--) {
		if (s[j] == '-') {
			nums = -nums;
			break;
		}
		nums += (s[j] - '0') * temp;
		temp *= 10;
	}
	result = nums;
	return result;
}


void menu(string s, Stack* res, Stack* revRes) {
	cout << "Введите 1, если хотите преобразовать введенное выражение в прямую польскую нотацию:\n";
	cout << "Введите 2, если хотите преобразовать введенное выражение в обратную польскую нотацию:\n";
	cout << "Введите 3, если хотите проверить введенное выражение на правильность прямой польской нотации:\n";
	cout << "Введите 4, если хотите проверить введенное выражение на правильность обратной польской нотации:\n";
	cout << "Введите 5, если хотите реализовать вычисление выражения, записанного в прямой польской нотации:\n";
	cout << "Введите 6, если хотите реализовать вычисление выражения, записанного в обратной польской нотации:\n";
	cout << "Введите 0, если хотите выйти:\n";
	int num;
	cin >> num;
	string s2;
	int resultRevP, resultP;
	switch (num) {
	case 1:
		system("cls");
		cout << "Ваше выражение:  " << s << "\n\n";
		res = Polnotation(s);
		cout << "\n\n";
		system("Pause");
		system("cls");
		menu(s, res, revRes);
		break;
	case 2:
		system("cls");
		cout << "Ваше выражение:  " << s << "\n\n";
		revRes = reversPolnotation(s);
		cout << "\n\n";
		system("Pause");
		system("cls");
		menu(s, res, revRes);
		break;
	case 3:
		system("cls");
		cout << "Ваше выражение:  " << s << "\n\n";
		cin.ignore();
		getline(cin, s2);
		cout << "\n\n";
		res = PolnotationDop(s);
		cout << "\n\n";
		corectPolnotation(res, s2);
		system("Pause");
		system("cls");
		menu(s, res, revRes);
		break;
	case 4:
		system("cls");
		cout << "Ваше выражение:  " << s << "\n\n";
		cin.ignore();
		getline(cin, s2);
		cout << "\n\n";
		revRes = reversPolnotationDop(s);
		cout << "\n\n";
		corectreversPolnotation(revRes, s2);
		system("Pause");
		system("cls");
		menu(s, res, revRes);
		break;
	case 5:
		system("cls");
		cout << "Ваше выражение:  " << s << "\n\n";
		if (res != 0) {
			res = PolnotationDop(s);
			resultP = resPolnotation(res);
			cout << "\n" << "Результат:   " << resultP << "\n\n";
		}
		else {
			cout << '\n' << "Сначала выполните пункт по созданию польской нотации\n\n";
		}
		system("Pause");
		system("cls");
		menu(s, res, revRes);
		break;
	case 6:
		system("cls");
		cout << "Ваше выражение:  " << s << "\n\n";
		if (revRes != 0) {
			revRes = reversPolnotationDop(s);
			resultRevP = resRevPolnotation(revRes);
			cout << "\n" << "Результат:   " << resultRevP << "\n\n";
		}
		else {
			cout << '\n' << "Сначала выполните пункт по созданию обратной польской нотации\n\n";
		}
		system("Pause");
		system("cls");
		menu(s, res, revRes);
		break;
	case 0:
		exit(0);
	default:
		cout << "Введено неправильное число, повторите ввод\n\n";
		system("Pause");
		system("cls");
		menu(s, res, revRes);
		break;
	}
}



int main() {
	setlocale(0, "");
	string s;
	cout << "Введите выражение:\n\n";
	getline(cin, s);
	inPerem(s);
	bool flag;
	flag = corectExpression(s);
	if (!flag) {
		cout << "\n\n" << "Введенное выражение не коректно\n\n";
		main();
	}
	else {
		cout << "\n\n" << "Выражение записано правильно, продолжаем\n\n";
	}
	Stack* res = 0;
	Stack* revRes = 0;
	system("Pause");
	system("cls");
	menu(s, res, revRes);
	return 0;
}