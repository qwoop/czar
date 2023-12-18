#include "czar-state-machine.h"

StateMachine *czar_state_machine_init() {

    StateMachine *state_machine = malloc(sizeof(StateMachine));
    fsmachine_initialize(state_machine);

    /* Q0 (STARTING STATE) */
    int start_idx = fsmachine_state_add(state_machine, false, T_ERROR);

    /* Q1 (IDENTIFIER) */
    int ident_idx = fsmachine_state_add(state_machine, true, T_IDENT);

    /* start -> identifier state */
    fsmachine_transition_add(
        state_machine, start_idx,
        charset_excludes(IDENTIFIER_SET, "abcdefgilnostw0123456789"),
        ident_idx);

    // identifier state to identifier state (self-loop)
    fsmachine_transition_add(state_machine, ident_idx,
                             charset_create(IDENTIFIER_SET), ident_idx);

    /* ########## KEYWORDS ########## */

    /* ========== A ========== */
    int a_idx = fsmachine_state_add(state_machine, true, T_IDENT);
    int an_idx = fsmachine_state_add(state_machine, true, T_IDENT);
    int and_idx = fsmachine_state_add(state_machine, true, T_AND);
    int as_idx = fsmachine_state_add(state_machine, true, T_AS);

    /* Q0 -> a */
    fsmachine_transition_add(state_machine, start_idx, charset_create("a"),
                             a_idx);

    /* a -> identifier state */
    fsmachine_transition_add(state_machine, a_idx,
                             charset_excludes(IDENTIFIER_SET, "ns"), ident_idx);

    /* ===== and ===== */

    /* a -> an */
    fsmachine_transition_add(state_machine, a_idx, charset_create("n"), an_idx);

    /* an -> identifier state */
    fsmachine_transition_add(state_machine, an_idx,
                             charset_excludes(IDENTIFIER_SET, "d"), ident_idx);

    /* an -> and */
    fsmachine_transition_add(state_machine, an_idx, charset_create("d"),
                             and_idx);

    /* and -> identifier state */
    fsmachine_transition_add(state_machine, and_idx,
                             charset_create(IDENTIFIER_SET), ident_idx);

    /* a -> as */
    fsmachine_transition_add(state_machine, a_idx, charset_create("s"), as_idx);

    /* as -> identifier state */
    fsmachine_transition_add(state_machine, as_idx,
                             charset_create(IDENTIFIER_SET), ident_idx);

    /* ========== B ========== */
    int b_idx = fsmachine_state_add(state_machine, true, T_IDENT);
    int by_idx = fsmachine_state_add(state_machine, true, T_BY);

    /* q0 - > b */
    fsmachine_transition_add(state_machine, start_idx, charset_create("b"),
                             a_idx);

    /* b -> identifier state */
    fsmachine_transition_add(state_machine, b_idx,
                             charset_excludes(IDENTIFIER_SET, "y"), ident_idx);

    /* ===== by ===== */

    /* b -> by */
    fsmachine_transition_add(state_machine, b_idx, charset_create("y"), by_idx);

    /* by -> identifier state */
    fsmachine_transition_add(state_machine, by_idx,
                             charset_create(IDENTIFIER_SET), ident_idx);

    /* ========== C ========== */
    int c_idx = fsmachine_state_add(state_machine, true, T_IDENT);
    int ch_idx = fsmachine_state_add(state_machine, true, T_IDENT);
    int chr_idx = fsmachine_state_add(state_machine, true, T_DTYPE);

    /* ===== chr ===== */

    /* q0 -> c */
    fsmachine_transition_add(state_machine, start_idx, charset_create("c"),
                             c_idx);

    /* c -> identifier state */
    fsmachine_transition_add(state_machine, c_idx,
                             charset_excludes(IDENTIFIER_SET, "h"), ident_idx);

    /* c -> ch */
    fsmachine_transition_add(state_machine, c_idx, charset_create("h"), ch_idx);

    /* ch -> identifier state */
    fsmachine_transition_add(state_machine, ch_idx,
                             charset_excludes(IDENTIFIER_SET, "r"), ident_idx);

    /* chr -> identifier state */
    fsmachine_transition_add(state_machine, chr_idx,
                             charset_create(IDENTIFIER_SET), ident_idx);

    /* ch -> chr */
    fsmachine_transition_add(state_machine, ch_idx, charset_create("r"),
                             chr_idx);

    /* ========== D ========== */
    int d_idx = fsmachine_state_add(state_machine, true, T_IDENT);
    int db_idx = fsmachine_state_add(state_machine, true, T_IDENT);
    int dbl_idx = fsmachine_state_add(state_machine, true, T_DTYPE);

    /* ===== dbl ===== */
    fsmachine_transition_add(state_machine, start_idx, charset_create("d"),
                             d_idx);

    /* d -> identifier state */
    fsmachine_transition_add(state_machine, d_idx,
                             charset_excludes(IDENTIFIER_SET, "b"), ident_idx);

    /* d -> db */
    fsmachine_transition_add(state_machine, d_idx, charset_create("b"), db_idx);

    /* db -> identifier state */
    fsmachine_transition_add(state_machine, db_idx,
                             charset_excludes(IDENTIFIER_SET, "l"), ident_idx);

    /* db -> dbl */
    fsmachine_transition_add(state_machine, db_idx, charset_create("l"),
                             dbl_idx);

    /* dbl -> identifier state */
    fsmachine_transition_add(state_machine, dbl_idx,
                             charset_create(IDENTIFIER_SET), ident_idx);

    /* ========== E ========== */
    int e_idx = fsmachine_state_add(state_machine, true, T_IDENT);

    int el_idx = fsmachine_state_add(state_machine, true, T_IDENT);
    int els_idx = fsmachine_state_add(state_machine, true, T_IDENT);
    int else_idx = fsmachine_state_add(state_machine, true, T_ELSE);

    int en_idx = fsmachine_state_add(state_machine, true, T_IDENT);
    int enu_idx = fsmachine_state_add(state_machine, true, T_IDENT);
    int enum_idx = fsmachine_state_add(state_machine, true, T_ENUM);

    fsmachine_transition_add(state_machine, start_idx, charset_create("e"),
                             e_idx);

    fsmachine_transition_add(state_machine, e_idx,
                             charset_excludes(IDENTIFIER_SET, "ln"), ident_idx);

    /*  ===== else ===== */

    /* e --> el */
    fsmachine_transition_add(state_machine, e_idx, charset_create("l"), el_idx);

    /* el --> els */
    fsmachine_transition_add(state_machine, el_idx, charset_create("s"),
                             els_idx);

    /* el --> identifier */
    fsmachine_transition_add(state_machine, el_idx,
                             charset_excludes(IDENTIFIER_SET, "s"), ident_idx);

    /* els --> else */
    fsmachine_transition_add(state_machine, els_idx, charset_create("e"),
                             else_idx);

    /* els --> identifier */
    fsmachine_transition_add(state_machine, els_idx,
                             charset_excludes(IDENTIFIER_SET, "e"), ident_idx);

    /* else --> identifier */
    fsmachine_transition_add(state_machine, else_idx,
                             charset_create(IDENTIFIER_SET), ident_idx);

    /* ===== enum ===== */

    /* e --> en */
    fsmachine_transition_add(state_machine, e_idx, charset_create("n"), en_idx);

    /* en -> enu */
    fsmachine_transition_add(state_machine, en_idx, charset_create("u"),
                             enu_idx);

    /* en -> identifier */
    fsmachine_transition_add(state_machine, en_idx,
                             charset_excludes(IDENTIFIER_SET, "u"), ident_idx);

    /* enu -> enum */
    fsmachine_transition_add(state_machine, enu_idx, charset_create("m"),
                             enum_idx);

    /* enu -> identifier */
    fsmachine_transition_add(state_machine, enu_idx,
                             charset_excludes(IDENTIFIER_SET, "m"), ident_idx);

    /* enum -> identifier */
    fsmachine_transition_add(state_machine, enum_idx,
                             charset_create(IDENTIFIER_SET), ident_idx);

    /* ========== F ========== */
    int f_idx = fsmachine_state_add(state_machine, true, T_IDENT);

    int fa_idx = fsmachine_state_add(state_machine, true, T_IDENT);
    int fal_idx = fsmachine_state_add(state_machine, true, T_IDENT);
    int fals_idx = fsmachine_state_add(state_machine, true, T_IDENT);
    int false_idx = fsmachine_state_add(state_machine, true, T_FALSE);

    int fi_idx = fsmachine_state_add(state_machine, true, T_IDENT);
    int fix_idx = fsmachine_state_add(state_machine, true, T_IDENT);
    int fixe_idx = fsmachine_state_add(state_machine, true, T_IDENT);
    int fixed_idx = fsmachine_state_add(state_machine, true, T_FIXED);

    int fl_idx = fsmachine_state_add(state_machine, true, T_IDENT);
    int fle_idx = fsmachine_state_add(state_machine, true, T_IDENT);
    int flex_idx = fsmachine_state_add(state_machine, true, T_FLEX);

    /* ===== false ===== */
    /* ===== fixed ===== */
    /* ===== flex ===== */

    /* ========== G ========== */
    int g_idx = fsmachine_state_add(state_machine, true, T_IDENT);
    int gl_idx = fsmachine_state_add(state_machine, true, T_IDENT);
    int glo_idx = fsmachine_state_add(state_machine, true, T_IDENT);
    int glob_idx = fsmachine_state_add(state_machine, true, T_IDENT);
    int globa_idx = fsmachine_state_add(state_machine, true, T_IDENT);
    int global_idx = fsmachine_state_add(state_machine, true, T_GLOBAL);

    /* ===== global ===== */

    /* ========== I ========== */
    int i_idx = fsmachine_state_add(state_machine, true, T_IDENT);
    int in_idx = fsmachine_state_add(state_machine, true, T_IN);

    int inp_idx = fsmachine_state_add(state_machine, true, T_IDENT);
    int inpu_idx = fsmachine_state_add(state_machine, true, T_IDENT);
    int input_idx = fsmachine_state_add(state_machine, true, T_INPUT);

    int int_idx = fsmachine_state_add(state_machine, true, T_INT);
    int is_idx = fsmachine_state_add(state_machine, true, T_IS);

    /* ===== in ===== */
    /* ===== input ===== */
    /* ===== int ===== */
    /* ===== is ===== */

    /* ========== L ========== */
    int l_idx = fsmachine_state_add(state_machine, true, T_IDENT);
    int lo_idx = fsmachine_state_add(state_machine, true, T_IDENT);
    int loo_idx = fsmachine_state_add(state_machine, true, T_IDENT);
    int loop_idx = fsmachine_state_add(state_machine, true, T_LOOP);

    /* ===== loop ===== */

    /* ========== N ========== */
    int n_idx = fsmachine_state_add(state_machine, true, T_IDENT);

    int ni_idx = fsmachine_state_add(state_machine, true, T_IDENT);
    int nil_idx = fsmachine_state_add(state_machine, true, T_NIL);

    int no_idx = fsmachine_state_add(state_machine, true, T_IDENT);
    int not_idx = fsmachine_state_add(state_machine, true, T_NOT);

    /* ===== nil ===== */
    /* ===== not ===== */

    /* ========== O ========== */
    int o_idx = fsmachine_state_add(state_machine, true, T_IDENT);

    int r_idx = fsmachine_state_add(state_machine, true, T_OR);

    int ou_idx = fsmachine_state_add(state_machine, true, T_IDENT);
    int out_idx = fsmachine_state_add(state_machine, true, T_IDENT);
    int outp_idx = fsmachine_state_add(state_machine, true, T_IDENT);
    int outpu_idx = fsmachine_state_add(state_machine, true, T_IDENT);
    int output_idx = fsmachine_state_add(state_machine, true, T_OUTPUT);

    /* ===== or ===== */
    /* ===== output ===== */

    /* ========== S ========== */

    int s_idx = fsmachine_state_add(state_machine, true, T_IDENT);
    int st_idx = fsmachine_state_add(state_machine, true, T_IDENT);
    int str_idx = fsmachine_state_add(state_machine, true, T_DTYPE);

    /* ===== str ===== */

    /* ========== T ========== */

    int t_idx = fsmachine_state_add(state_machine, true, T_IDENT);

    int th_idx = fsmachine_state_add(state_machine, true, T_IDENT);
    int the_idx = fsmachine_state_add(state_machine, true, T_IDENT);
    int then_idx = fsmachine_state_add(state_machine, true, T_THEN);

    int to_idx = fsmachine_state_add(state_machine, true, T_TO);

    int tr_idx = fsmachine_state_add(state_machine, true, T_IDENT);
    int tru_idx = fsmachine_state_add(state_machine, true, T_IDENT);
    int true_idx = fsmachine_state_add(state_machine, true, T_TRUE);

    /* ===== then ===== */
    /* ===== to ===== */
    /* ===== true ===== */

    /* ========== W ========== */

    int w_idx = fsmachine_state_add(state_machine, true, T_IDENT);
    int wh_idx = fsmachine_state_add(state_machine, true, T_IDENT);

    int whe_idx = fsmachine_state_add(state_machine, true, T_IDENT);
    int when_idx = fsmachine_state_add(state_machine, true, T_WHEN);

    int whi_idx = fsmachine_state_add(state_machine, true, T_IDENT);
    int whil_idx = fsmachine_state_add(state_machine, true, T_IDENT);
    int while_idx = fsmachine_state_add(state_machine, true, T_WHILE);

    /* ===== when ===== */
    /* ===== while ===== */

    /* ########## FLOAT ########## */

    int digit_idx = fsmachine_state_add(state_machine, true, T_INT);
    int decimal_point_idx =
        fsmachine_state_add(state_machine, false, T_INVALID);
    int decimal_digit_idx = fsmachine_state_add(state_machine, true, T_DBL);
    int dead_decimal_point_idx =
        fsmachine_state_add(state_machine, false, T_ERROR);

    /* ===== digit ===== */
    fsmachine_transition_add(state_machine, start_idx, charset_create(DIGITS),
                             digit_idx);
    fsmachine_transition_add(state_machine, start_idx, charset_create("."),
                             decimal_point_idx);
    fsmachine_transition_add(state_machine, digit_idx, charset_create(DIGITS),
                             digit_idx);
    fsmachine_transition_add(state_machine, digit_idx, charset_create("."),
                             decimal_point_idx);

    /* ===== decimal ===== */
    fsmachine_transition_add(state_machine, decimal_point_idx,
                             charset_create(DIGITS), decimal_digit_idx);
    fsmachine_transition_add(state_machine, decimal_point_idx,
                             charset_create("."), dead_decimal_point_idx);

    /* ===== decimal digit ===== */
    fsmachine_transition_add(state_machine, decimal_digit_idx,
                             charset_create(DIGITS), decimal_digit_idx);
    fsmachine_transition_add(state_machine, decimal_digit_idx,
                             charset_create("."), dead_decimal_point_idx);

    /* ===== DEAD decimal digit ===== */
    fsmachine_transition_add(state_machine, dead_decimal_point_idx,
                             charset_includes(DIGITS, "."),
                             dead_decimal_point_idx);

    /* ########## STRING ########## */

    int left_dquotation_idx =
        fsmachine_state_add(state_machine, false, T_DQUOTE);
    int string_idx = fsmachine_state_add(state_machine, false, T_STR);
    int right_dquotation_idx =
        fsmachine_state_add(state_machine, true, T_DQUOTE);
    int string_error_idx = fsmachine_state_add(state_machine, true, T_ERROR);

    /* ===== left double quotation ===== */
    fsmachine_transition_add(state_machine, start_idx, charset_create("\""),
                             left_dquotation_idx);

    /* ===== quotation error ===== */
    fsmachine_transition_add(state_machine, left_dquotation_idx,
                             charset_create("\n\""), string_error_idx);

    /* ===== string ===== */
    fsmachine_transition_add(state_machine, left_dquotation_idx,
                             charset_excludes(STRING_SET, "\n\""), string_idx);
    fsmachine_transition_add(state_machine, string_idx,
                             charset_excludes(STRING_SET, "\n\""), string_idx);

    /* ===== string error  ===== */
    fsmachine_transition_add(state_machine, string_idx, charset_create("\n"),
                             string_error_idx);

    fsmachine_null_terminator_transition_add(state_machine, string_idx,
                                             string_error_idx);

    /* ===== right double quotation ===== */
    fsmachine_transition_add(state_machine, string_idx, charset_create("\""),
                             right_dquotation_idx);

    /* ########## CHARACTER ########## */

    int left_squotation_idx =
        fsmachine_state_add(state_machine, false, T_SQUOTE);
    int character_idx = fsmachine_state_add(state_machine, false, T_CHR);
    int right_squotation_idx =
        fsmachine_state_add(state_machine, true, T_SQUOTE);
    int character_error_idx = fsmachine_state_add(state_machine, true, T_ERROR);

    /* ===== left single quotation ===== */
    fsmachine_transition_add(state_machine, start_idx, charset_create("'"),
                             left_squotation_idx);

    /* ===== quotation error ===== */
    fsmachine_transition_add(state_machine, left_squotation_idx,
                             charset_create("\n'"), character_error_idx);

    /* ===== character ===== */
    fsmachine_transition_add(state_machine, left_squotation_idx,
                             charset_excludes(STRING_SET, "\n'"),
                             character_idx);

    /* ===== character error  ===== */
    fsmachine_transition_add(state_machine, character_idx,
                             charset_excludes(STRING_SET, "'"),
                             character_error_idx);

    /* ===== right single quotation ===== */
    fsmachine_transition_add(state_machine, character_idx, charset_create("'"),
                             right_squotation_idx);

    /* ########## ARRAY ########## */

    int left_bracket_idx =
        fsmachine_state_add(state_machine, false, T_LBRACKET);
    int right_bracket_idx =
        fsmachine_state_add(state_machine, true, T_RBRACKET);
    int array_error = fsmachine_state_add(state_machine, true, T_ERROR);

    /* ===== LEFT BRACKET  ===== */
    fsmachine_transition_add(state_machine, start_idx, charset_create("["),
                             left_bracket_idx);

    /* ===== ARRAY ERROR  ===== */
    fsmachine_transition_add(state_machine, left_bracket_idx,
                             charset_create("]"), array_error);
    fsmachine_transition_add(state_machine, left_bracket_idx,
                             charset_excludes(IDENTIFIER_SET, "cdis"),
                             array_error);

    /* ===== CHAR ARRAY ===== */
    int chr_arr_c_idx = fsmachine_state_add(state_machine, false, T_CHR);
    int chr_arr_h_idx = fsmachine_state_add(state_machine, false, T_CHR);
    int chr_arr_r_idx = fsmachine_state_add(state_machine, false, T_CHR);

    fsmachine_transition_add(state_machine, left_bracket_idx,
                             charset_create("c"), chr_arr_c_idx);
    fsmachine_transition_add(state_machine, chr_arr_c_idx, charset_create("h"),
                             chr_arr_h_idx);
    fsmachine_transition_add(state_machine, chr_arr_h_idx, charset_create("r"),
                             chr_arr_r_idx);
    fsmachine_transition_add(state_machine, chr_arr_r_idx, charset_create("]"),
                             right_bracket_idx);

    /* ===== chr array error  ===== */
    fsmachine_transition_add(state_machine, chr_arr_c_idx,
                             charset_excludes(IDENTIFIER_SET, "h"),
                             array_error);
    fsmachine_transition_add(state_machine, chr_arr_h_idx,
                             charset_excludes(IDENTIFIER_SET, "r"),
                             array_error);
    fsmachine_transition_add(state_machine, chr_arr_r_idx,
                             charset_excludes(STRING_SET, "]"), array_error);

    /* ===== DBL ARRAY ===== */
    int dbl_arr_d_idx = fsmachine_state_add(state_machine, false, T_DBL);
    int dbl_arr_b_idx = fsmachine_state_add(state_machine, false, T_DBL);
    int dbl_arr_l_idx = fsmachine_state_add(state_machine, false, T_DBL);

    fsmachine_transition_add(state_machine, left_bracket_idx,
                             charset_create("d"), dbl_arr_d_idx);
    fsmachine_transition_add(state_machine, dbl_arr_d_idx, charset_create("b"),
                             dbl_arr_b_idx);
    fsmachine_transition_add(state_machine, dbl_arr_b_idx, charset_create("l"),
                             dbl_arr_l_idx);
    fsmachine_transition_add(state_machine, dbl_arr_l_idx, charset_create("]"),
                             right_bracket_idx);

    /* ===== dbl array error  ===== */
    fsmachine_transition_add(state_machine, dbl_arr_d_idx,
                             charset_excludes(IDENTIFIER_SET, "b"),
                             array_error);
    fsmachine_transition_add(state_machine, dbl_arr_b_idx,
                             charset_excludes(IDENTIFIER_SET, "l"),
                             array_error);
    fsmachine_transition_add(state_machine, dbl_arr_l_idx,
                             charset_excludes(STRING_SET, "]"), array_error);

    /* ===== INT ARRAY ===== */
    int int_arr_i_idx = fsmachine_state_add(state_machine, false, T_INT);
    int int_arr_n_idx = fsmachine_state_add(state_machine, false, T_INT);
    int int_arr_t_idx = fsmachine_state_add(state_machine, false, T_INT);

    fsmachine_transition_add(state_machine, left_bracket_idx,
                             charset_create("i"), int_arr_i_idx);
    fsmachine_transition_add(state_machine, int_arr_i_idx, charset_create("n"),
                             int_arr_n_idx);
    fsmachine_transition_add(state_machine, int_arr_n_idx, charset_create("t"),
                             int_arr_t_idx);
    fsmachine_transition_add(state_machine, int_arr_t_idx, charset_create("]"),
                             right_bracket_idx);

    /* ===== int array error  ===== */
    fsmachine_transition_add(state_machine, int_arr_i_idx,
                             charset_excludes(IDENTIFIER_SET, "n"),
                             array_error);
    fsmachine_transition_add(state_machine, int_arr_n_idx,
                             charset_excludes(IDENTIFIER_SET, "t"),
                             array_error);
    fsmachine_transition_add(state_machine, int_arr_t_idx,
                             charset_excludes(STRING_SET, "]"), array_error);

    /* ===== STR ARRAY ===== */
    int str_arr_s_idx = fsmachine_state_add(state_machine, false, T_STR);
    int str_arr_t_idx = fsmachine_state_add(state_machine, false, T_STR);
    int str_arr_r_idx = fsmachine_state_add(state_machine, false, T_STR);

    fsmachine_transition_add(state_machine, left_bracket_idx,
                             charset_create("s"), str_arr_s_idx);
    fsmachine_transition_add(state_machine, str_arr_s_idx, charset_create("t"),
                             str_arr_t_idx);
    fsmachine_transition_add(state_machine, str_arr_t_idx, charset_create("r"),
                             str_arr_r_idx);
    fsmachine_transition_add(state_machine, str_arr_r_idx, charset_create("]"),
                             right_bracket_idx);

    /* ===== str array error  ===== */
    fsmachine_transition_add(state_machine, str_arr_s_idx,
                             charset_excludes(IDENTIFIER_SET, "t"),
                             array_error);
    fsmachine_transition_add(state_machine, str_arr_t_idx,
                             charset_excludes(IDENTIFIER_SET, "r"),
                             array_error);
    fsmachine_transition_add(state_machine, str_arr_r_idx,
                             charset_excludes(STRING_SET, "]"), array_error);

    /* ########## OPERATION SYMBOLS ########## */

    /* ===== arithmetic operation ===== */
    int plus_idx = fsmachine_state_add(state_machine, true, T_PLUS);
    int minus_idx = fsmachine_state_add(state_machine, true, T_MINUS);
    int mul_idx = fsmachine_state_add(state_machine, true, T_MUL);
    int div_idx = fsmachine_state_add(state_machine, true, T_DIV);
    int modulo_idx = fsmachine_state_add(state_machine, false, T_MOD);
    int exponent_idx = fsmachine_state_add(state_machine, false, T_EXP);
    int not_abs_idx = fsmachine_state_add(state_machine, true, T_ERROR);
    int abs_idx = fsmachine_state_add(state_machine, false, T_ABS);

    /* Q0 -> + */
    fsmachine_transition_add(state_machine, start_idx, charset_create("+"),
                             plus_idx);

    /* Q0 -> - */
    fsmachine_transition_add(state_machine, start_idx, charset_create("-"),
                             minus_idx);

    /* Q0 -> * */
    fsmachine_transition_add(state_machine, start_idx, charset_create("*"),
                             mul_idx);

    /* Q0 -> / */
    fsmachine_transition_add(state_machine, start_idx, charset_create("/"),
                             div_idx);

    /* Q0 -> % */
    fsmachine_transition_add(state_machine, start_idx, charset_create("%"),
                             modulo_idx);

    /* Q0 -> ^ */
    fsmachine_transition_add(state_machine, start_idx, charset_create("^"),
                             exponent_idx);
    
    /* Q0 -> | */
    fsmachine_transition_add(state_machine, start_idx, charset_create("|"),
                             not_abs_idx);

    /* | -> || */
    fsmachine_transition_add(state_machine, not_abs_idx, charset_create("|"),
                             abs_idx);
    

    /* ===== shorthand operation ===== */
    int plus_eql_idx = fsmachine_state_add(state_machine, false, T_PLUS_EQL);
    int minus_eql_idx = fsmachine_state_add(state_machine, false, T_MINUS_EQL);
    int mul_eql_idx = fsmachine_state_add(state_machine, false, T_MUL_EQL);
    int div_eql_idx = fsmachine_state_add(state_machine, false, T_DIV_EQL);

    /* + -> += */
    fsmachine_transition_add(state_machine, plus_idx, charset_create("="),
                             plus_eql_idx);

    /* - -> -= */
    fsmachine_transition_add(state_machine, minus_idx, charset_create("="),
                             minus_eql_idx);

    /* * -> *= */
    fsmachine_transition_add(state_machine, mul_idx, charset_create("="),
                             mul_eql_idx);

    /* / -> /= */
    fsmachine_transition_add(state_machine, div_idx, charset_create("="),
                             div_eql_idx);                                                                           

    /* ########## WHITESPACES ########## */
    int return_idx = fsmachine_state_add(state_machine, true, T_INVALID);
    int newline_idx = fsmachine_state_add(state_machine, true, T_NEWLINE);

    /* Q0 - space -> Q0 */
    fsmachine_transition_add(state_machine, start_idx, charset_create(" "),
                             start_idx);

    /* Q0 --> /r */
    fsmachine_transition_add(state_machine, start_idx, charset_create("\r"),
                             return_idx);

    /* /r -> newline */
    fsmachine_transition_add(state_machine, return_idx, charset_create("\n"),
                             newline_idx);

    /* Q0 --> newline */
    fsmachine_transition_add(state_machine, start_idx, charset_create("\n"),
                             newline_idx);

    return state_machine;
}