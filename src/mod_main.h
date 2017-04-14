#ifndef MOD_MAIN_H
#define MOD_MAIN_H

#ifdef __cplusplus
extern "C"  {
#endif

typedef struct
{
    char*   mod_path;
    int     port;
}stMOD_MAIN_PARA_T, *pstMOD_MAIN_PARA_T;

int mod_main_init(pstMOD_MAIN_PARA_T ppara);
int mod_main_loop();
int mod_main_fini();

#ifdef __cplusplus
}
#endif


#endif // MOD_MAIN_H
