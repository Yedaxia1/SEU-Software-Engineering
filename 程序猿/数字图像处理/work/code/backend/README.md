## QiaoQian backend
- Create a new app
```bat
python manage.py startapp ...(app name)
```

- Run django server (just for develop!)
```bat
python manage.py runserver
```

- Migrate
```bat
python manage.py makemigrations
python manage.py migrate
```
- Note
    - ***DO NOT operate tables directly. You should always use Django ORM Model.***