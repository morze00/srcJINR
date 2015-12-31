// ----------------------------------------------------------------------
//                    UniDbShift header file 
//                      Generated 05-11-2015 
// ----------------------------------------------------------------------

/** db_classes/UniDbShift.h 
 ** Class for the table: shift_ 
 **/ 

#ifndef UNIDBSHIFT_H 
#define UNIDBSHIFT_H 1 

#include "TString.h"
#include "TDatime.h"

#include "UniDbConnection.h"

class UniDbShift
{
 private:
	/* GENERATED PRIVATE MEMBERS (SHOULDN'T BE CHANGED MANUALLY) */
	/// connection to the database
	UniDbConnection* connectionUniDb;

	/// shift id
	int i_shift_id;
	/// period number
	int i_period_number;
	/// start datetime
	TDatime dt_start_datetime;
	/// end datetime
	TDatime dt_end_datetime;
	/// fio
	TString str_fio;
	/// responsibility
	TString* str_responsibility;

	//Constructor
	UniDbShift(UniDbConnection* connUniDb, int shift_id, int period_number, TDatime start_datetime, TDatime end_datetime, TString fio, TString* responsibility);
	/* END OF PRIVATE GENERATED PART (SHOULDN'T BE CHANGED MANUALLY) */

 public:
	/* GENERATED PUBLIC MEMBERS (SHOULDN'T BE CHANGED MANUALLY) */
	virtual ~UniDbShift(); // Destructor

	// static class functions
	/// add new shift to the database
	static UniDbShift* CreateShift(int period_number, TDatime start_datetime, TDatime end_datetime, TString fio, TString* responsibility);
	/// get shift from the database
	static UniDbShift* GetShift(int shift_id);
	/// delete shift from the database
	static int DeleteShift(int shift_id);
	/// print all shifts
	static int PrintAll();

	// Getters
	/// get shift id of the current shift
	int GetShiftId() {return i_shift_id;}
	/// get period number of the current shift
	int GetPeriodNumber() {return i_period_number;}
	/// get start datetime of the current shift
	TDatime GetStartDatetime() {return dt_start_datetime;}
	/// get end datetime of the current shift
	TDatime GetEndDatetime() {return dt_end_datetime;}
	/// get fio of the current shift
	TString GetFio() {return str_fio;}
	/// get responsibility of the current shift
	TString* GetResponsibility() {if (str_responsibility == NULL) return NULL; else return new TString(*str_responsibility);}

	// Setters
	/// set shift id of the current shift
	int SetShiftId(int shift_id);
	/// set period number of the current shift
	int SetPeriodNumber(int period_number);
	/// set start datetime of the current shift
	int SetStartDatetime(TDatime start_datetime);
	/// set end datetime of the current shift
	int SetEndDatetime(TDatime end_datetime);
	/// set fio of the current shift
	int SetFio(TString fio);
	/// set responsibility of the current shift
	int SetResponsibility(TString* responsibility);
	/// print information about current shift
	void Print();
	/* END OF PUBLIC GENERATED PART (SHOULDN'T BE CHANGED MANUALLY) */

 ClassDef(UniDbShift,1);
};

#endif