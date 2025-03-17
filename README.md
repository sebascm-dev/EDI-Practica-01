# EDI-Practica-01

## Instrucciones para conectar al repositorio

Sigue estos pasos para conectar esta carpeta al repositorio remoto y subir cambios:

### 1. Inicializar el repositorio Git

Si el repositorio aún no está inicializado, ejecuta:

```bash
git init
```

### 2. Solucionar problema de directorio seguro (si ocurre)

Si encuentras un error de "dubious ownership", ejecuta:

```bash
git config --global --add safe.directory C:/Users/spano/Downloads/EDI-Practica-01
```

### 3. Añadir el repositorio remoto

Conecta tu repositorio local al repositorio remoto:

```bash
git remote add origin https://github.com/sebascm-dev/EDI-Practica-01.git
```

### 4. Añadir archivos al área de preparación

Añade todos los archivos:

```bash
git add .
```

O añade archivos específicos:

```bash
git add archivo1.py archivo2.py
```

### 5. Confirmar (commit) los cambios

Realiza un commit con un mensaje descriptivo:

```bash
git commit -m "Descripción de los cambios realizados"
```

### 6. Subir (push) los cambios al repositorio remoto

Para la primera vez:

```bash
git push -u origin master
```

o si usas la rama 'main':

```bash
git push -u origin main
```

Para futuras actualizaciones:

```bash
git push
```

## Solución de problemas comunes

- Si aparece el error de "dubious ownership", utiliza el comando de safe.directory mencionado en el paso 2.
- Si el push es rechazado, puede que necesites hacer un pull primero: `git pull origin main`

