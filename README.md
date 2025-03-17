# EDI-Practica-01

## Instrucciones para conectar al repositorio
### 1. Inicializar el repositorio Git

```bash
git init
```

### 2. Solucionar problema de directorio seguro (si ocurre)

```bash
git config --global --add safe.directory C:/Users/spano/Downloads/EDI-Practica-01
```

### 3. Añadir el repositorio remoto

```bash
git remote add origin https://github.com/sebascm-dev/EDI-Practica-01.git
```

### 4. Añadir archivos al área de preparación

```bash
git add .
```

### 5. Confirmar (commit) los cambios

```bash
git commit -m "Descripción de los cambios realizados"
```

### 6. Subir (push) los cambios al repositorio remoto

Para la primera vez del repositorio:

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

