ARRAY8 ar1@@RANDOM_ID_1@@ 4
ARRAY(CREATE8, 4, ar1@@RANDOM_ID_1@@)
ARRAY_WRITE(ar1@@RANDOM_ID_1@@, 0, 1)
ARRAY_WRITE(ar1@@RANDOM_ID_1@@, 1, 66)
ARRAY8 answer@@RANDOM_ID_2@@ 4
ARRAY(CREATE8, 4, answer@@RANDOM_ID_2@@)
DATA8 fst@@RANDOM_ID_3@@
DATA8 snd@@RANDOM_ID_4@@
DATA32 fst32@@RANDOM_ID_5@@
DATA32 snd32@@RANDOM_ID_6@@
DATA8 flag@@RANDOM_ID_7@@

INPUT_DEVICE(SETUP, 0, @@PORT@@, 1, 0, 2, @ar1@@RANDOM_ID_1@@, 2, @answer@@RANDOM_ID_2@@)

ARRAY_READ(answer@@RANDOM_ID_2@@, 0, fst@@RANDOM_ID_3@@)
ARRAY_READ(answer@@RANDOM_ID_2@@, 1, snd@@RANDOM_ID_4@@)

MOVE8_32(snd@@RANDOM_ID_4@@, snd32@@RANDOM_ID_6@@)
AND8(snd@@RANDOM_ID_4@@, -128 ,flag@@RANDOM_ID_7@@)
JR_NEQ8(flag@@RANDOM_ID_7@@, -128, m1@@RANDOM_ID_8@@)
AND32(snd32@@RANDOM_ID_6@@, 127, snd32@@RANDOM_ID_6@@)
ADD32(snd32@@RANDOM_ID_6@@, 128, snd32@@RANDOM_ID_6@@)
m1@@RANDOM_ID_8@@:
MOVE8_32(fst@@RANDOM_ID_3@@, fst32@@RANDOM_ID_5@@) // data = 2 * snd + fst(0/1)
MUL32(snd32@@RANDOM_ID_6@@, 2, snd32@@RANDOM_ID_6@@)
ADD32(snd32@@RANDOM_ID_6@@, fst32@@RANDOM_ID_5@@, @@RESULT@@)
ARRAY(DELETE, answer@@RANDOM_ID_2@@)
ARRAY(DELETE, ar1@@RANDOM_ID_1@@)