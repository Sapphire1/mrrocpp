// -------------------------------------------------------------------------
//                            servo_gr.h
// Definicje struktur danych i metod dla procesu SERVO_GROUP
//
// Ostatnia modyfikacja: 16.04.98
// -------------------------------------------------------------------------

#ifndef __EDP_REGULATOR_H
#define __EDP_REGULATOR_H

#include "base/lib/com_buf.h"
#include "base/edp/edp_typedefs.h"

namespace mrrocpp {
namespace edp {
namespace common {

enum REG_OUTPUT
{
	CURRENT_OUTPUT, PWM_OUTPUT
};

static const uint8_t ALGORITHM_AND_PARAMETERS_OK = 0;
static const uint8_t UNIDENTIFIED_ALGORITHM_NO = 1;
static const uint8_t UNIDENTIFIED_ALGORITHM_PARAMETERS_NO = 2;

/*-----------------------------------------------------------------------*/
class regulator
{
	/* Klasa bazowa (i abstrakcyjna) dla poszczegolnych regulatorow konkretnych */

protected:

	// Zmienne lokalne klasy oraz funkcje wykorzystywane jedynie
	// wewnatrz tej klasy, tzn. przez algorytm regulacji.
	// Niezaleznie od zmiennych uzywanych przez algorytm konkretny
	// ponizsze zmienne musza byc zawsze aktualizowany, ze wzgledu na
	// "bezszelestne" przelaczanie algorytmow.

	int measured_current; // wartosc zmierzona pradu

	double position_increment_old; // przedosatnio odczytany przyrost polozenie (delta y[k-2]
	// -- mierzone w impulsach)
	double position_increment_new; // ostatnio odczytany przyrost polozenie (delta y[k-1]
	// -- mierzone w impulsach)
	double pos_increment_new_sum; // suma odczytanych przyrostow polozenia w trakcie realizacji makrokroku
	// (mierzona w impulsach)// by Y dla EDP_master
	double servo_pos_increment_new_sum; // suma odczytanych przyrostow polozenia w trakcie realizacji makrokroku
	// (mierzona w impulsach)// by Y dla EDP_servo
	double step_old_pulse; // poprzednia wartosc zadana dla jednego kroku regulacji
	// (przyrost wartosci zadanej polozenia -- delta r[k-2]
	// -- mierzone w radianach)
	double step_new; // nastepna wartosc zadana dla jednego kroku regulacji
	// (przyrost wartosci zadanej polozenia -- delta r[k-1]
	// -- mierzone w radianach)
	double step_old; // poprzednia wartosc zadana dla jednego kroku regulacji
	// (przyrost wartosci zadanej polozenia -- delta r[k-1]
	// -- mierzone w radianach)

	double step_new_over_constraint_sum;

	double output_value; // wyjscie, z reguly set_value_new
	double set_value_new; // wielkosc kroku do realizacji przez HI (wypelnienie PWM -- u[k])
	double set_value_old; // wielkosc kroku do realizacji przez HI (wypelnienie PWM -- u[k-1])
	double set_value_very_old; // wielkosc kroku do realizacji przez HI (wypelnienie PWM -- u[k-2])
	double delta_eint; // przyrost calki uchybu
	double delta_eint_old; // przyrost calki uchybu w poprzednim kroku

	int PWM_value; // zadane wypelnienie PWM
	uint8_t algorithm_no; // przeslany numer algorytmu
	uint8_t current_algorithm_no; // numer aktualnie uzywanego algorytmu
	uint8_t algorithm_parameters_no; // przeslany numer zestawu parametrow algorytmu
	uint8_t current_algorithm_parameters_no; // numer aktualnie uzywanego zestawu parametrow algorytmu

	lib::GRIPPER_STATE_ENUM reg_state, next_reg_state, prev_reg_state; // stany w ktorych moze byc regulator

	// uchyb polozenia osi
	double abs_pos_dev;
	// uchyb polozenia osi w poprzednim kroku
	double abs_pos_dev_old;
	// przyrost uchybu polozenia wzgledem poprzedniego kroku
	double delta_abs_pos_dev;
	// calka uchybu (od poczatku ruchu)
	double abs_pos_dev_int;
	// calka uchybu w poprzednim kroku
	double abs_pos_dev_int_old;

	// maksymalny predkosc zadana (przyrost na jeden krok) w radianach na wale silnika
	double desired_velocity_limit;

public:

	REG_OUTPUT reg_output;

	bool new_desired_velocity_error;
	// samoświadomości osi
	uint8_t axis_number;

	motor_driven_effector &master;
	regulator(uint8_t _axis_number, uint8_t reg_no, uint8_t reg_par_no, motor_driven_effector &_master, REG_OUTPUT _reg_output); // konstruktor

	virtual ~regulator();

	virtual uint8_t compute_set_value(void) = 0;
	// obliczenie nastepnej wartosci zadanej dla napedu - metoda abstrakcyjna

	double get_set_value(void) const;

	// regulator desired abs position for particular step
	double reg_abs_desired_motor_pos;

	// regulator current abs position for particular step
	double reg_abs_current_motor_pos;

	double previous_abs_position; // poprzednia pozycja absolutna dla potrzeb trybu testowego
	void insert_new_step(double ns);
	void insert_measured_current(int measured_current_l);

	double return_new_step() const;

	double get_previous_pwm() const;

	void insert_new_pos_increment(double inc);

	double get_position_inc(int tryb);

	int get_measured_current(void) const;

	int get_PWM_value(void) const;

	// do odczytu stanu regulatora (w szczegolnosci regulatora chwytaka)
	int get_reg_state(void) const;

	int get_actual_inc(void) const;

	// double get_desired_inc ( int axe_nr );

	void insert_algorithm_no(uint8_t new_number);

	uint8_t get_algorithm_no(void) const;

	void insert_algorithm_parameters_no(uint8_t new_number);

	uint8_t get_algorithm_parameters_no(void) const;

	void clear_regulator(void);
};
/*-----------------------------------------------------------------------*/

/*-----------------------------------------------------------------------*/
class NL_regulator : public regulator
{
	/* Klasa regulatorow konkretnych */
	// Obiekt z algorytmem regulacji
protected:
	// zmienne lokalne klasy oraz funkcje wykorzystywane jedynie
	//  wewnatrz tej klasy, tzn. przez algorytm regulacji
	double a, b0, b1; // parametry regulatora
	double k_feedforward; // wzmocnienie w petli "feedforward"
	double EPS; // Dokladnosc zera dla przyrostow
	unsigned int integrator_off; // Liczba krokow zerowego PWM po ktorej wylaczmy calkowanie
	unsigned int counter; // Licznik krokow zerowego PWM
	double MAX_PWM;

	double int_current_error;
	int display;

	double max_output_current;
	double current_reg_kp;
	double step_new_pulse; // nastepna wartosc zadana dla jednego kroku regulacji

public:

	NL_regulator(uint8_t _axis_number, uint8_t reg_no, uint8_t reg_par_no, double aa, double bb0, double bb1, double k_ff, motor_driven_effector &_master, REG_OUTPUT _reg_output);

	virtual uint8_t compute_set_value(void) = 0;
	// obliczenie nastepnej wartosci zadanej dla napedu - metoda abstrakcyjna

	virtual ~NL_regulator();

	void compute_set_value_final_computations();

};
// ----------------------------------------------------------------------

}// namespace common
} // namespace edp
} // namespace mrrocpp

#endif
