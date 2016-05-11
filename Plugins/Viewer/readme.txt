tcsh
cd NewViewer
setenv LD_LIBRARY_PATH $PWD/viewer/bin
setenv LC_NUMERIC "C"
setenv VEDITOR gedit
setenv VIMAGE eog
setenv MAKEFLAGS --quiet
setenv VPLUGINS "libdraw-vbo-ext.so;libshaderloader.so;libnavigatedefault.so"   
setenv VPLUGINS "libdraw-vbo-ext.so;librenderdefault.so;libnavigatedefault.so"   
make
viewer/bin/viewerd

---------------------

doxygen 
pushd viewer/core; doxygen; popd
pushd viewer/glwidget; doxygen; popd
pushd viewer/interfaces; doxygen; popd

Para editar la config de doxygen: 
    doxywizard Doxyfile

----------------

Limpiar la solucion 

make clean
rm Makefile
rm *~
rm viewer/Makefile
rm -r viewer/bin

rm viewer/app/Makefile
rm -r viewer/app/build
rm -r viewer/app/include/*~
rm -r viewer/app/src/*~


rm  viewer/core/Makefile
rm -r viewer/core/build
rm -r viewer/core/include/*~
rm -r viewer/core/src/*~

rm viewer/glwidget/Makefile
rm -r viewer/glwidget/build
rm -r viewer/glwidget/include/*~
rm -r viewer/glwidget/src/*~

rm plugins/Makefile
rm -r plugins/bin

rm -r plugins/draw-vbo-ext/Makefile
rm -r plugins/draw-vbo-ext/*~
rm -r plugins/draw-vbo-ext/build

rm -r plugins/navigate-default/Makefile
rm -r plugins/navigate-default/*~
rm -r plugins/navigate-default/build

rm -r plugins/render-default/Makefile
rm -r plugins/render-default/*~
rm -r plugins/render-default/build

rm -r plugins/shaderLoader/Makefile
rm -r plugins/shaderLoader/*~
rm -r plugins/shaderLoader/build

rm -r plugins/alphablending/Makefile
rm -r plugins/alphablending/*~
rm -r plugins/alphablending/build

rm -r plugins/auto-update/Makefile
rm -r plugins/auto-update/*~
rm -r plugins/auto-update/build

rm -r plugins/drawimmediate/Makefile
rm -r plugins/drawimmediate/*~
rm -r plugins/drawimmediate/build

rm -r plugins/effect-crt/Makefile
rm -r plugins/effect-crt/*~
rm -r plugins/effect-crt/build

rm -r plugins/show-help/Makefile
rm -r plugins/show-help/*~
rm -r plugins/show-help/build




Manualmente eliminar, de la copia del estudiante:
readme.txt
todos los plugins excepto:
    draw-vbo-ext, navigate, render, shaderLoader,
    show-help, effect-crt, auto-update, drawimmediate


------------------
Syntax highlight in gedit

mkdir ~/.local/share/gtksourceview-3.0/
mkdir ~/.local/share/gtksourceview-3.0/language-specs
cp /assig/grau-g/glsl330.lang ~/.local/share/gtksourceview-3.0/language-specs/

----

Snippets for gedit

mkdir ./.config/
mkdir ./.config/gedit/
mkdir ./.config/gedit/snippets/
cp /assig/grau-g/glsl.xml ./.config/gedit/snippets/glsl.xml


----
cd NewViewer
export LD_LIBRARY_PATH=$PWD/viewer/bin
export LC_NUMERIC="C"
make
viewer/bin/viewer


-------------------------

cd ~/NewViewer/plugins/edges

rm edges.cpp edges.frag tmp
cp ~/Descargas/C2/P34643_albert.martinez.g/Entregats/edges.* .
cat edges.cpp | sed 's/fs->compile.*;/fs->compileSourceFile("\/home\/andujar\/NewViewer\/plugins\/edges\/edges.frag");/g' > tmp ; cp tmp edges.cpp
make clean ; rm Makefile ; qmake ; make
alias v ../../viewer/bin/viewer
alias g grep Color edges.cpp
alias h grep g edges.frag

-----------------------------------------------

find *.test -type f -exec ../NewViewer/viewer/bin/viewerd '{}' \;
find . -name '*.test' | xargs head -1
 find . -name '*.test' | xargs sed -i 's/resize 600 600/resize 512 512/g'


--------------------------------

    TODO LIST

--------------------------------

Viewer:
- Box::render() usa modo inmediato
- Completar uniforms disponibles en ShaderLoader::paintGL()  (vec2, vec3...)
- guardar out o ref .png dependiendo de var entorno (profe)








