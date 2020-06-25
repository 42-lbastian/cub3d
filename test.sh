make re

echo "\033[1m\033[4mBienvenue sur le destructeur de parsing\033[0m"
echo ""

echo "Test Mauvaise Map\033[91m(M)\033[0m - Mauvais Chemin\033[91m(C)\033[0m - Ligne Vide\033[91m(V)\033[0m - Valeurs F&C\033[91m(F)\033[0m - Parasite\033[91m(P)\033[0m - Resolution\033[91m(R)\033[0m - Extension\033[91m(E)\033[0m - Fichier Valide\033[91m(G)\033[0m - Inexistant\033[91m(I)\033[0m - Leaks\033[94m(L)\033[0m - Tout\033[35m(T)\033[0m"
read rep

echo ""

if [ $rep = 'M' ] || [ $rep = 'T' ]
then

	echo "\033[91mTest Mauvaises Map\033[0m"

	echo ""
	echo "\033[35mbad_map_1\033[0m"
	./Cub3D maps_test/bad_map_1.cub
	echo ""
	echo "\033[35mbad_map_2\033[0m"
	./Cub3D maps_test/bad_map_2.cub
	echo ""
	echo "\033[35mbad_map_3\033[0m"
	./Cub3D maps_test/bad_map_3.cub
	echo ""
	echo "\033[35mbad_map_4\033[0m"
	./Cub3D maps_test/bad_map_4.cub
	echo ""
	echo "\033[35mbad_map_4.5\033[0m"
	./Cub3D maps_test/bad_map_4_5.cub
	echo ""
	echo "\033[35mbad_map_5\033[0m"
	./Cub3D maps_test/bad_map_5.cub
	echo ""
	echo "\033[35mbad_map_6\033[0m"
	./Cub3D maps_test/bad_map_6.cub
	echo ""
	echo "\033[35mbad_map_7\033[0m"
	./Cub3D maps_test/bad_map_7.cub
	echo ""

fi

if [ $rep = 'C' ] || [ $rep = 'T' ]
then

	echo "\033[91mTest Mauvais chemin\033[0m"

	echo ""
	echo "\033[35mbad_path_1\033[0m"
	./Cub3D maps_test/bad_path_1.cub
	echo ""
	echo "\033[35mbad_path_2\033[0m"
	./Cub3D maps_test/bad_path_2.cub
	echo ""
	echo "\033[35mbad_path_3\033[0m"
	./Cub3D maps_test/bad_path_3.cub
	echo ""
	echo "\033[35mbad_path_4\033[0m"
	./Cub3D maps_test/bad_path_4.cub
	echo ""
	echo "\033[35mbad_path_5\033[0m"
	./Cub3D maps_test/bad_path_5.cub
	echo ""
	echo "\033[35mbad_path_all\033[0m"
	./Cub3D maps_test/bad_path_all.cub
	echo ""

fi

if [ $rep = 'V' ] || [ $rep = 'T' ]
then

	echo "\033[91mTest ligne vide\033[0m"

	echo ""
	echo "\033[35mempty_line_1\033[0m"
	./Cub3D maps_test/empty_line_1.cub
	echo ""
	echo "\033[35mempty_line_2\033[0m"
	./Cub3D maps_test/empty_line_2.cub
	echo ""
	echo "\033[35mempty_line_3\033[0m"
	./Cub3D maps_test/empty_line_3.cub
	echo ""

fi

if [ $rep = 'F' ] || [ $rep = 'T' ]
then

	echo "\033[91mTest valeurs negatives ceilling - floor\033[0m"

	echo ""
	echo "\033[35mless_than_0_1_c\033[0m"
	./Cub3D maps_test/less_than_0_1_c.cub
	echo ""
	echo "\033[35mless_than_0_2_c\033[0m"
	./Cub3D maps_test/less_than_0_2_c.cub
	echo ""
	echo "\033[35mless_than_0_3_c\033[0m"
	./Cub3D maps_test/less_than_0_3_c.cub
	echo ""

	echo "\033[35mless_than_0_1_f\033[0m"
	./Cub3D maps_test/less_than_0_1_f.cub
	echo ""
	echo "\033[35mless_than_0_2_f\033[0m"
	./Cub3D maps_test/less_than_0_2_f.cub
	echo ""
	echo "\033[35mless_than_0_3_f\033[0m"
	./Cub3D maps_test/less_than_0_3_f.cub
	echo ""

	echo "\033[91mTest valeurs sup a 255 ceilling - floor\033[0m"

	echo ""
	echo "\033[35mmore_than_255_1_c\033[0m"
	./Cub3D maps_test/more_than_255_1_c.cub
	echo ""
	echo "\033[35mmore_than_255_2_c\033[0m"
	./Cub3D maps_test/more_than_255_2_c.cub
	echo ""
	echo "\033[35mmore_than_255_3_c\033[0m"
	./Cub3D maps_test/more_than_255_3_c.cub

	echo ""
	echo "\033[35mmore_than_255_1_f\033[0m"
	./Cub3D maps_test/more_than_255_1_f.cub
	echo ""
	echo "\033[35mmore_than_255_2_f\033[0m"
	./Cub3D maps_test/more_than_255_2_f.cub
	echo ""
	echo "\033[35mmore_than_255_3_f\033[0m"
	./Cub3D maps_test/more_than_255_3_f.cub
	echo ""

	echo "\033[91mOnly Comma\033[0m"
	echo ""
	echo "\033[35monly_comma_c\033[0m"
	./Cub3D maps_test/only_comma_c.cub
	echo ""
	echo "\033[35monly_comma_f\033[0m"
	./Cub3D maps_test/only_comma_f.cub
	echo ""

fi

if [ $rep = 'P' ] || [ $rep = 'T' ]
then

	echo "\033[91mTest texte parasite\033[0m"

	echo ""
	echo "\033[35mparasite_1\033[0m"
	./Cub3D maps_test/parasite_1.cub
	echo ""
	echo "\033[35mparasite_2\033[0m"
	./Cub3D maps_test/parasite_2.cub
	echo ""
	echo "\033[35mparasite_3\033[0m"
	./Cub3D maps_test/parasite_3.cub
	echo ""
	echo "\033[35mparasite_4\033[0m"
	./Cub3D maps_test/parasite_4.cub
	echo ""
	echo "\033[35mparasite_5\033[0m"
	./Cub3D maps_test/parasite_5.cub
	echo ""
	echo "\033[35mparasite_6\033[0m"
	./Cub3D maps_test/parasite_6.cub
	echo ""
	echo "\033[35mparasite_7\033[0m"
	./Cub3D maps_test/parasite_7.cub
	echo ""
	echo "\033[35mparasite_8\033[0m"
	./Cub3D maps_test/parasite_8.cub
	echo ""

	echo "\033[91mTest texte apres map\033[0m"
	echo ""
	echo "\033[35mafter_map_1\033[0m"
	./Cub3D maps_test/after_map_1.cub
	echo ""
	echo "\033[35mafter_map_2\033[0m"
	./Cub3D maps_test/after_map_2.cub
	echo ""


fi

if [ $rep = 'R' ] || [ $rep = 'T' ]
then

	echo "\033[91mTest resolution\033[0m"

	echo ""
	echo "\033[35mresolution_1\033[0m"
	./Cub3D maps_test/resolution_1.cub
	echo ""
	echo "\033[35mresolution_2\033[0m"
	./Cub3D maps_test/resolution_2.cub
	echo ""
	echo "\033[35mresolution_3\033[0m"
	./Cub3D maps_test/resolution_3.cub
	echo ""
	echo "\033[35mresolution_4\033[0m"
	./Cub3D maps_test/resolution_4.cub
	echo ""

fi

if [ $rep = 'E' ] || [ $rep = 'T' ]
then

	echo "\033[91mTest extension cub\033[0m"

	echo ""
	echo "\033[35mextension_cub\033[0m"
	./Cub3D maps_test/extension_cub
	echo ""

	echo "\033[91mTest extension xpm\033[0m"
	
	echo ""
	echo "\033[35mnot_xpm_1\033[0m"
	./Cub3D maps_test/not_xpm_1.cub
	echo ""
	echo "\033[35mnot_xpm_2\033[0m"
	./Cub3D maps_test/not_xpm_2.cub
	echo ""
	echo "\033[35mnot_xpm_3\033[0m"
	./Cub3D maps_test/not_xpm_3.cub
	echo ""
	echo "\033[35mnot_xpm_4\033[0m"
	./Cub3D maps_test/not_xpm_4.cub
	echo ""
	echo "\033[35mnot_xpm_5\033[0m"
	./Cub3D maps_test/not_xpm_5.cub
	echo ""


fi

if [ $rep = 'G' ] || [ $rep = 'T' ]
then

	echo "\033[91mTest Bon fichier\033[0m"

	echo ""
	echo "\033[35mgood_map_1\033[0m"
	./Cub3D maps_test/good_map_1.cub
	echo ""

fi

if [ $rep = 'I' ] || [ $rep = 'T' ]
then

	echo "\033[91mTest Fichier inexistant\033[0m"

	echo ""
	echo "\033[35mNIK.cub\033[0m"
	./Cub3D maps_test/NIK.cub
	echo ""

	echo "\033[91mMultiple arguments\033[0m"

	echo ""
	echo "\033[35mgood_map_1 && toto\033[0m"
	./Cub3D maps_test/good_map_1.cub toto.cub
	echo ""
	echo "\033[35mNIK.cub\033[0m"
	./Cub3D maps_test/good_map_1.cub maps_test/good_map_1.cub
	echo ""



fi

if [ $rep = 'L' ] || [ $rep = 'T' ]
then


gcc srcs/*.c -g

echo "\033[94mLEAKS\033[0m"
echo ""

echo "\033[35mgood_map_1\033[0m"
EXEC=a.out;ARGS=maps_test/good_map_1.cub;valgrind --tool=memcheck --leak-check=full --leak-resolution=high --show-reachable=yes --log-file=valgrind_log ./$EXEC $ARGS
grep -iR "Definitely lost:" valgrind_log
echo ""

echo "\033[35mbad_map_1\033[0m"
EXEC=a.out;ARGS=maps_test/bad_map_1.cub;valgrind --tool=memcheck --leak-check=full --leak-resolution=high --show-reachable=yes --log-file=valgrind_log ./$EXEC $ARGS
grep -iR "Definitely lost:" valgrind_log
echo ""

echo "\033[35mbad_path_1\033[0m"
EXEC=a.out;ARGS=maps_test/bad_path_1.cub;valgrind --tool=memcheck --leak-check=full --leak-resolution=high --show-reachable=yes --log-file=valgrind_log ./$EXEC $ARGS
grep -iR "Definitely lost:" valgrind_log
echo ""

echo "\033[35mempty_line_1\033[0m"
EXEC=a.out;ARGS=maps_test/empty_line_1.cub;valgrind --tool=memcheck --leak-check=full --leak-resolution=high --show-reachable=yes --log-file=valgrind_log ./$EXEC $ARGS
grep -iR "Definitely lost:" valgrind_log
echo ""

echo "\033[35mempty_line_2\033[0m"
EXEC=a.out;ARGS=maps_test/empty_line_2.cub;valgrind --tool=memcheck --leak-check=full --leak-resolution=high --show-reachable=yes --log-file=valgrind_log ./$EXEC $ARGS
grep -iR "Definitely lost:" valgrind_log
echo ""

echo "\033[35mparasite_1\033[0m"
EXEC=a.out;ARGS=maps_test/parasite_1.cub;valgrind --tool=memcheck --leak-check=full --leak-resolution=high --show-reachable=yes --log-file=valgrind_log ./$EXEC $ARGS
grep -iR "Definitely lost:" valgrind_log
echo ""

echo "\033[35mparasite_6\033[0m"
EXEC=a.out;ARGS=maps_test/parasite_6.cub;valgrind --tool=memcheck --leak-check=full --leak-resolution=high --show-reachable=yes --log-file=valgrind_log ./$EXEC $ARGS
grep -iR "Definitely lost:" valgrind_log
echo ""

echo "\033[35mafter_map_1\033[0m"
EXEC=a.out;ARGS=maps_test/after_map_1.cub;valgrind --tool=memcheck --leak-check=full --leak-resolution=high --show-reachable=yes --log-file=valgrind_log ./$EXEC $ARGS
grep -iR "Definitely lost:" valgrind_log
echo ""

echo "\033[35mNIK.cub\033[0m"
EXEC=a.out;ARGS=maps_test/NIK.cub;valgrind --tool=memcheck --leak-check=full --leak-resolution=high --show-reachable=yes --log-file=valgrind_log ./$EXEC $ARGS
grep -iR "Definitely lost:" valgrind_log
echo ""

echo "\033[35mnot_xpm_1\033[0m"
EXEC=a.out;ARGS=maps_test/not_xpm_1.cub;valgrind --tool=memcheck --leak-check=full --leak-resolution=high --show-reachable=yes --log-file=valgrind_log ./$EXEC $ARGS
grep -iR "Definitely lost:" valgrind_log
echo ""

echo "\033[35mextension_cub\033[0m"
EXEC=a.out;ARGS=maps_test/extension_cub;valgrind --tool=memcheck --leak-check=full --leak-resolution=high --show-reachable=yes --log-file=valgrind_log ./$EXEC $ARGS
grep -iR "Definitely lost:" valgrind_log
echo ""

echo "\033[35mmultiple_arg - good_map_1 && toto\033[0m"
EXEC=a.out;valgrind --tool=memcheck --leak-check=full --leak-resolution=high --show-reachable=yes --log-file=valgrind_log ./$EXEC maps_test/good_map_1.cub toto.cub 
grep -iR "Definitely lost:" valgrind_log
echo ""

echo "\033[35mmultiple_arg - good_map_1 && good_map_1\033[0m"
EXEC=a.out;valgrind --tool=memcheck --leak-check=full --leak-resolution=high --show-reachable=yes --log-file=valgrind_log ./$EXEC maps_test/good_map_1.cub maps_test/good_map_1.cub
grep -iR "Definitely lost:" valgrind_log
echo ""

fi
