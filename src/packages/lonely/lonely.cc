// Written by Clode@Revival World 2001/07/10

#include "base/package_api.h"
#include "packages/core/outbuf.h"

/* 取代原有 find_player() */
#ifdef NO_ADD_ACTION
void f_find_player () 
{
	
	int len;
	object_t *ob;
	char *name, path[26] = "/data/user/ /";
	
	name = (char *)sp->u.string;
	len = strlen(name)+13;
	
	if( len > 25 )
	{
		*sp = const0;
		return;
	}
	
	path[11] = name[0];
	
	len=13;
	while(*name) path[len++] = *name++;

	path[len] = '\0';
	 
	ob = find_object2(path);

	free_string_svalue(sp);
	
	if (ob && object_visible(ob))
		put_unrefed_undested_object(ob, "find_player");
	else
		*sp = const0;
}
#endif

/*
  用来中止一个互动物件的 input_to 状态
*/
#ifdef F_REMOVE_INPUT_TO
void f_remove_input_to ()
{
    object_t *ob;

    if (st_num_arg) 
	{
		ob = sp->u.ob;
		pop_stack();
    }
    else ob = current_object;
    
    if( ob->interactive != 0 )
    {
    	ob->interactive->carryover = NULL;
    	ob->interactive->num_carry = 0;
    	ob->interactive->input_to = 0;
    }
}
#endif


/* 
  去除字串两端的空白字元
*/
#ifdef F_REMOVE_FRINGE_BLANKS
void f_remove_fringe_blanks () 
{
	int len;
	char *str, *res;
	
	str = (char *)sp->u.string;

	while( uisspace(*str) ) str++;
	
	len = strlen(str);

	while( len && uisspace(str[len-1]) ) len--; 
	
	str[len]='\0';

	res = new_string(len, "f_remove_fringe_blanks");
	strncpy(res, str, len+1);
	
	free_string_svalue(sp);
	put_malloced_string(res);
}
#endif

#ifdef F_BUFTOSTR
void f_buftostr()
{
    char *ret = new_string(sp->u.buf->size, "f_to_string");
   
    ret[sp->u.buf->size] = '\0';
    memcpy(ret, sp->u.buf->item, sp->u.buf->size);
   
    free_buffer(sp->u.buf);
    put_malloced_string(ret);
}
#endif

#ifdef F_STRTOBUF
void f_strtobuf()
{
    int len = SVALUE_STRLEN(sp);
    buffer_t *buf = allocate_buffer(len);

    memcpy(buf->item, sp->u.string, len);
    
    pop_stack();
    push_refed_buffer(buf);
}
#endif

#ifdef F_MILLI_CLOCK
void
f_milli_clock (void)
{
	struct timeval tv;
	struct timezone tz;
	time_t msec;
	gettimeofday(&tv, &tz);
	msec = (tv.tv_sec-boot_time)*1000+ (tv.tv_usec / 1000);
	push_number(msec);

}
#endif

#ifdef F_LUAN
void
f_luan (void)
{
    debug_message("%s\n",sp->u.string);
    pop_stack();
}
#endif

