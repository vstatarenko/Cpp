#include "interpolation.h"

float LagrangeInterpolation::Interpolation(const float x, const short polynom_degree){
	FindDomain(x);
	float l = 0.0;
	for (short i = 0; i <= polynom_degree; i++)
	{
		float l_coeff = 1.0;
		for (short j = 0; j <= polynom_degree; j++) {
			if (i != j)
				l_coeff *= (x - domain.at(j).x) / (domain.at(i).x - domain.at(j).x);
		}
		l += l_coeff*domain.at(i).y;
	}
	return l;
}

/*
Чтобы вычислить многочлен Лагранжа F_k(x0) k-ой степени
функции f(x) в точке х0, нужно выбрать k+1 пар узлов
функции f(x) : a = x1 < x2 < ... < x_k+1 = b из всей
совокупности узлов. При этом должно выполняться a<= x0 <=b. 
Данная функция вычисляет (пока не оптимально) такие
 пары (узел, значение)
*/
void LagrangeInterpolation::FindDomain(const float x)
{
	int x0_index;
	domain.clear();
	try {
		for (int i = 0; i < GetNodeNumb() - n; i++) {
			bool interval_founded = false;
			for (int j = 0; j <= n; j++) {
				float x0 = GetPoint(i + j).x;
				if (x <= x0 ) {
					x0_index = i;
					interval_founded = true;
					break;
				}
			}
			if (interval_founded)
				break;
		}
		for (int j = 0; j <= n; j++)
			domain.push_back(GetPoint(x0_index + j));
	}
	catch (std::logic_error const& err) {
		throw(err.what());
	}
}


