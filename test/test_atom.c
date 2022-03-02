#include "cii.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void test_atom()
{
    printf("---------------test atomic--------------\n");

    int x = 12345;
    long y = 12345678;
    const char *z = "test atomic";
    const char *a = "another atomic string";

    const char *zz = "test atomic";
    const char *aa = "another atomic string";

    const char *test_x = Atom_int(x);
    const char *test_y = Atom_int(y);
    const char *test_z = Atom_new(z, strlen(z));
    const char *test_a = Atom_string(a);
    const char *test_zz = Atom_string(zz);
    const char *test_aa = Atom_string(aa);
    printf("atomic x is \"%s\"\n", test_x);
    printf("atomic y is \"%s\"\n", test_y);
    printf("atomic z is \"%s\"\n", test_z);
    printf("atomic a is \"%s\"\n", test_a);
    printf("atomic zz is \"%s\"\n", test_zz);
    printf("atomic aa is \"%s\"\n", test_aa);

    char str_x[32] = {'\0'};
    sprintf(str_x, "%d", x);
    // int len_x = Atom_length(str_x); //Warning: Atom_length is used only for atomic string!
    int len_x = Atom_length(test_x);
    printf("x in string type:%s, len:%zu, len in atom:%d\n", str_x, strlen(str_x), len_x);

    char str_y[32] = {'\0'};
    sprintf(str_y, "%ld", y);
    // int len_y = Atom_length(str_y);
    int len_y = Atom_length(test_y); //Warning: Atom_length is used only for atomic string!
    printf("y in string type:%s, len:%zu, len in atom:%d\n", str_y, strlen(str_y), len_y);

    // int len_z = Atom_length(z); //Warning: Atom_length is used only for atomic string!
    int len_z = Atom_length(test_z);
    // int len_a = Atom_length(a); //Warning: Atom_length is used only for atomic string!
    int len_a = Atom_length(test_a);
    printf("z in string type:\"%s\", len:%zu, len in atom:%d, addr:0x%p\n", z, strlen(z), len_z, test_z);
    printf("a in string type:\"%s\", len:%zu, len in atom:%d, addr:0x%p\n", a, strlen(a), len_a, test_a);

    int len_zz =Atom_length(test_zz);
    int len_aa = Atom_length(test_aa);
    printf("zz in string type:\"%s\", len:%zu, len in atom:%d, addr:0x%p\n", zz, strlen(zz), len_zz, test_zz);
    printf("aa in string type:\"%s\", len:%zu, len in atom:%d, addr:0x%p\n", aa, strlen(aa), len_aa, test_aa);

    printf("\n\n");
}