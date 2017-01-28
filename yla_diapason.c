#include "yla_diapason.h"

void put_number_in_diapason(yla_int_type **prog_ptr, yla_int_type subprog_start_addr, compliance_table *compliance, yla_int_type *prog_counter, yla_int_type global_var[])
{
	yla_int_type prog_count = *prog_counter;
	
	yla_int_type ret = global_var[0];
	yla_int_type i = global_var[1];
	
	compliance_table_set_addr(compliance, subprog_start_addr, prog_count);
	
	put_commd(prog_ptr, CSAVE);						prog_count++;
	put_value(prog_ptr, ret);						prog_count += 2;
	
	// Local vars section
	// i = start
	put_commd(prog_ptr, CDUP);						prog_count++;
	put_value(prog_ptr, 0x0003);					prog_count += 2;
	put_commd(prog_ptr, CSAVE);						prog_count++;
	put_value(prog_ptr, i);							prog_count += 2;
	// End local vars section
	
	// while (i < end)
	/*while_start(61)*/
	compliance_table_set_addr(compliance, 0x0061, prog_count);
	put_commd(prog_ptr, CDUP);						prog_count++;
	put_value(prog_ptr, 0x0001);					prog_count += 2;
	put_commd(prog_ptr, CLOAD);						prog_count++;
	put_value(prog_ptr, i);							prog_count += 2;
	
	put_commd(prog_ptr, CJG);						prog_count++;
	put_value(prog_ptr, 0x0068);					prog_count += 2;	/*ret_no(68)*/
	// {
	put_commd(prog_ptr, CSTK);						prog_count++;
	put_value(prog_ptr, 0x0002);					prog_count += 2;
	
	// if (i == number)
	put_commd(prog_ptr, CLOAD);						prog_count++;
	put_value(prog_ptr, i);							prog_count += 2;
	put_commd(prog_ptr, CDUP);						prog_count++;
	put_value(prog_ptr, 0x0001);					prog_count += 2;
	put_commd(prog_ptr, CCMP);						prog_count++;
	// { CJNZ yes
	put_commd(prog_ptr, CJNZ);						prog_count++;
	put_value(prog_ptr, 0x0067);					prog_count += 2;	/*ret_yes(67)*/
	
	// }
	put_commd(prog_ptr, CSTK);						prog_count++;
	put_value(prog_ptr, 0x0001);					prog_count += 2;
	
	// i += step
	put_commd(prog_ptr, CLOAD);						prog_count++;
	put_value(prog_ptr, i);							prog_count += 2;
	put_commd(prog_ptr, CDUP);						prog_count++;
	put_value(prog_ptr, 0x0003);					prog_count += 2;
	put_commd(prog_ptr, CADD);						prog_count++;
	put_commd(prog_ptr, CSAVE);						prog_count++;
	put_value(prog_ptr, i);							prog_count += 2;
	
	// } (while)
	put_commd(prog_ptr, CJMP);						prog_count++;
	put_value(prog_ptr, 0x0061);					prog_count += 2;	/*while_start(61)*/
	
	/*ret_yes(67)*/
	compliance_table_set_addr(compliance, 0x0067, prog_count);
	put_commd(prog_ptr, CSTK);						prog_count++;
	put_value(prog_ptr, 0x0001);					prog_count += 2;
	put_commd(prog_ptr, CPUSH);						prog_count++;
	put_value(prog_ptr, 0x0001);					prog_count += 2;
	put_commd(prog_ptr, CJMP);						prog_count++;
	put_value(prog_ptr, 0x0069);					prog_count += 2;	/*ret(99)*/
	
	/*ret_no(98)*/
	compliance_table_set_addr(compliance, 0x0068, prog_count);
	put_commd(prog_ptr, CSTK);						prog_count++;
	put_value(prog_ptr, 0x0002);					prog_count += 2;
	put_commd(prog_ptr, CPUSH);						prog_count++;
	put_value(prog_ptr, 0x0000);					prog_count += 2;
	put_commd(prog_ptr, CJMP);						prog_count++;
	put_value(prog_ptr, 0x0069);					prog_count += 2;	/*ret(69)*/
	
	/*ret(69)*/
	compliance_table_set_addr(compliance, 0x0069, prog_count);
	put_commd(prog_ptr, CLOAD);						prog_count++;
	put_value(prog_ptr, ret);						prog_count += 2;
	put_commd(prog_ptr, CRET);						prog_count++;
	
	*prog_counter = prog_count;
}

void put_diap_number_post(yla_int_type **prog_ptr, yla_int_type subprog_start_addr, compliance_table *compliance, yla_int_type *prog_counter, yla_int_type global_var[])
{
	yla_int_type prog_count = *prog_counter;
	
	yla_int_type ret = global_var[0];
	
	compliance_table_set_addr(compliance, subprog_start_addr, prog_count);
	
	put_commd(prog_ptr, CSAVE);						prog_count++;
	put_value(prog_ptr, ret);						prog_count += 2;
	
	// Multiplicate start of diapason
	put_commd(prog_ptr, CDUP);						prog_count++;
	put_value(prog_ptr, 0x0000);					prog_count += 2;
	put_commd(prog_ptr, CDUP);						prog_count++;
	put_value(prog_ptr, 0x0004);					prog_count += 2;
	put_commd(prog_ptr, CMULT);						prog_count++;
	put_commd(prog_ptr, CDEEP);						prog_count++;
	put_value(prog_ptr, 0x0003);					prog_count += 2;
	
	// Multiplicate end of diapason
	put_commd(prog_ptr, CDUP);						prog_count++;
	put_value(prog_ptr, 0x0000);					prog_count += 2;
	put_commd(prog_ptr, CDUP);						prog_count++;
	put_value(prog_ptr, 0x0002);					prog_count += 2;
	put_commd(prog_ptr, CMULT);						prog_count++;
	put_commd(prog_ptr, CDEEP);						prog_count++;
	put_value(prog_ptr, 0x0001);					prog_count += 2;
	
	// Ret subprogram
	put_commd(prog_ptr, CLOAD);						prog_count++;
	put_value(prog_ptr, ret);						prog_count += 2;
	put_commd(prog_ptr, CRET);						prog_count++;
	
	*prog_counter = prog_count;
}

void put_diap_number_pre(yla_int_type **prog_ptr, yla_int_type subprog_start_addr, compliance_table *compliance, yla_int_type *prog_counter, yla_int_type global_var[])
{
	yla_int_type prog_count = *prog_counter;
	
	yla_int_type ret = global_var[0];
	yla_int_type i = global_var[1];
	
	compliance_table_set_addr(compliance, subprog_start_addr, prog_count);
	
	put_commd(prog_ptr, CSAVE);						prog_count++;
	put_value(prog_ptr, ret);						prog_count += 2;
	
	// Local vars section
	// i = 3 
	put_commd(prog_ptr, CPUSH);						prog_count++;
	put_value(prog_ptr, 0x0003);					prog_count += 2;
	put_commd(prog_ptr, CSAVE);						prog_count++;
	put_value(prog_ptr, i);							prog_count += 2;
	// End local vars section
	
	// Multiplicate start of diapason
	put_commd(prog_ptr, CDUP);						prog_count++;
	put_value(prog_ptr, 0x0003);					prog_count += 2;
	put_commd(prog_ptr, CDUP);						prog_count++;
	put_value(prog_ptr, 0x0003);					prog_count += 2;
	put_commd(prog_ptr, CMULT);						prog_count++;
	put_commd(prog_ptr, CDEEP);						prog_count++;
	put_value(prog_ptr, 0x0002);					prog_count += 2;
	
	// Multiplicate end of diapason
	put_commd(prog_ptr, CDUP);						prog_count++;
	put_value(prog_ptr, 0x0003);					prog_count += 2;
	put_commd(prog_ptr, CDUP);						prog_count++;
	put_value(prog_ptr, 0x0001);					prog_count += 2;
	put_commd(prog_ptr, CMULT);						prog_count++;
	put_commd(prog_ptr, CDEEP);						prog_count++;
	put_value(prog_ptr, 0x0000);					prog_count += 2;
	
	// Delete multiplicator from deep of stack
	
	// for (i = 3; i > 0; i--)
	/*offset_diapason(71)*/
	compliance_table_set_addr(compliance, 0x0071, prog_count);
	put_commd(prog_ptr, CLOAD);						prog_count++;
	put_value(prog_ptr, i);							prog_count += 2;
	put_commd(prog_ptr, CJZ);						prog_count++;
	put_value(prog_ptr, 0x0079);					prog_count += 2;	/*ret(79)*/
	// {
	put_commd(prog_ptr, CSTK);						prog_count++;
	put_value(prog_ptr, 0x0001);					prog_count += 2;
	// CGDUP i - 1:
	// a. (i - 1)
	put_commd(prog_ptr, CLOAD);						prog_count++;
	put_value(prog_ptr, i);							prog_count += 2;
	put_commd(prog_ptr, CPUSH);						prog_count++;
	put_value(prog_ptr, 0x0001);					prog_count += 2;
	put_commd(prog_ptr, CSUB);						prog_count++;
	put_commd(prog_ptr, CSAVE);						prog_count++;
	put_value(prog_ptr, i);							prog_count += 2;
	// b. CGDUP (i - 1)
	put_commd(prog_ptr, CGDUP);						prog_count++;
	put_value(prog_ptr, i);							prog_count += 2;
	
	// CGDEEP i:
	// a. (i + 1)
	put_commd(prog_ptr, CLOAD);						prog_count++;
	put_value(prog_ptr, i);							prog_count += 2;
	put_commd(prog_ptr, CPUSH);						prog_count++;
	put_value(prog_ptr, 0x0001);					prog_count += 2;
	put_commd(prog_ptr, CADD);						prog_count++;
	put_commd(prog_ptr, CSAVE);						prog_count++;
	put_value(prog_ptr, i);							prog_count += 2;
	// b. CGDEEP (i)
	put_commd(prog_ptr, CGDEEP);					prog_count++;
	put_value(prog_ptr, i);							prog_count += 2;
	
	// i--
	put_commd(prog_ptr, CLOAD);						prog_count++;
	put_value(prog_ptr, i);							prog_count += 2;
	put_commd(prog_ptr, CPUSH);						prog_count++;
	put_value(prog_ptr, 0x0001);					prog_count += 2;
	put_commd(prog_ptr, CSUB);						prog_count++;
	put_commd(prog_ptr, CSAVE);						prog_count++;
	put_value(prog_ptr, i);							prog_count += 2;
	
	// }
	put_commd(prog_ptr, CJMP);						prog_count++;
	put_value(prog_ptr, 0x0071);					prog_count += 2;	/*offset_diapason(71)*/
	
	// Ret subprogram
	/*ret(79)*/
	compliance_table_set_addr(compliance, 0x0079, prog_count);
	put_commd(prog_ptr, CSTK);						prog_count++;
	put_value(prog_ptr, 0x0002);					prog_count += 2;
	put_commd(prog_ptr, CLOAD);						prog_count++;
	put_value(prog_ptr, ret);						prog_count += 2;
	put_commd(prog_ptr, CRET);						prog_count++;
	
	*prog_counter = prog_count;
}