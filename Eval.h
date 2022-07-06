// #ifndef EVAL_H
// #define EVAL_H
//
// // EVERYTHING IS GLOBAL :3
// Lst *env;
//
// Lst *sum(Lst *lst)
// {
//     Lst *ret = newlst(T_NAT);
//     while(lst){
//         if(lst->type != T_NAT){
//             fprintf(stderr, "cant sum lst with type %s\n", TypeStr[lst->type]);
//             exit(EXIT_FAILURE);
//         }
//         ret->nat += lst->nat;
//         lst = lst->nxt;
//     }
//     return ret;
// }
//
// Lst *showDeep(Lst *lst)
// {
//     Lst *cur = lst;
//     while(cur){
//
//     }
// }
//
// Lst *con(Lst *a, Lst *b)
// {
//     Lst *ret = newlst(T_LST);
//     ret
// }
//
// Lst *searchEnv(char *name)
// {
//     Lst *cur = env;
//     while(cur){
//         if(cur->type == T_SYM && strlen(cur->sym.name) == len && !strncmp(cur->sym.name, name, len))
//             return cur;
//         cur = cur->nxt;
//     }
//     return NULL;
// }
//
// Lst *eval(Lst *ast, Lst *cur)
// {
//     while(cur){
//         Lst *found = NULL;
//         if(cur->type == T_SYM){
//             found = searchEnv(env, cur->sym.name, )
//         }
//     }
// }
//
// #endif /* end of include guard: EVAL_H */
