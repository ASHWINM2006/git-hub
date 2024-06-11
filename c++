<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Task Manager</title>
    <style>
        body {
            display: flex;
            justify-content: center;
            align-items: center;
            height: 100vh;
            margin: 0;
            font-family: 'Arial', sans-serif;
            color: #333;
        
        }

        .container {
          
            width: 90%;
            max-width: 600px;
            text-align: center;
            padding: 15px; /* Decreased padding */
            border-radius: 10px;
            box-shadow: 0 4px 8px rgba(0, 0, 0, 0.2);
            margin-top: 20px;
        }

        h1 {
            color: #333;
            margin-bottom: 15px; /* Decreased margin-bottom */
            font-size: 2.5em;
            text-shadow: 2px 2px 2px rgba(0, 0, 0, 0.1);
        }

        div, label, input, button {
            margin: 8px 0; /* Decreased margin */
            display: block;
            width: 100%;
        }

        label {
            text-align: left;
            font-weight: bold;
            margin-top: 10px; /* Decreased margin-top */
            color: #555;
        }

        input, textarea {
            padding: 8px; /* Decreased padding */
            width: calc(100% - 16px); /* Adjusted width accordingly */
            border: 1px solid #ccc;
            border-radius: 5px;
            box-sizing: border-box;
            font-size: 1em;
            color: #555;
            transition: border-color 0.3s ease-in-out;
        }

        input:focus, textarea:focus {
            outline: none;
            border-color: #6c5ce7;
        }

        button {
            padding: 8px 16px; /* Decreased padding */
            background-color: #6c5ce7;
            color: #fff;
            border: none;
            border-radius: 5px;
            cursor: pointer;
            transition: background-color 0.3s;
            margin-top: 15px; /* Decreased margin-top */
            font-size: 1em;
            text-transform: uppercase;
            letter-spacing: 1px;
            box-shadow: 0 4px 8px rgba(0, 0, 0, 0.2);
        }

        button:hover {
            background-color: #4834d4;
        }

        button:disabled {
            background-color: #ccc;
            cursor: not-allowed;
        }

        ul {
            list-style-type: none;
            padding: 0;
            margin-top: 15px; /* Decreased margin-top */
        }

        li {
            background: #f0f0f0;
            margin-bottom: 8px; /* Decreased margin-bottom */
            border: 1px solid #ddd;
            border-radius: 5px;
            padding: 10px; /* Decreased padding */
            display: flex;
            justify-content: space-between;
            align-items: center;
            transition: background-color 0.3s;
        }

        li:hover {
            background-color: #e0e0e0;
        }

        .task-item {
            display: flex;
            justify-content: space-between;
            align-items: center;
            width: 100%;
        }

        .task-item button {
            background-color: #ff6b6b;
            padding: 8px 12px; /* Decreased padding */
            border-radius: 5px;
            font-size: 0.9em;
            text-transform: uppercase;
            letter-spacing: 1px;
            cursor: pointer;
            transition: background-color 0.3s;
            border: none;
            color: #fff;
            box-shadow: 0 2px 4px rgba(0, 0, 0, 0.1);
        }

        .task-item button:hover {
            background-color: #ee5253;
        }

        .task-item .done {
            text-decoration: line-through;
            color: #6c757d;
        }

        .task-details {
            flex-grow: 1;
            text-align: left;
            padding-right: 8px; /* Decreased padding-right */
        }

        @media (max-width: 600px) {
            .container {
                width: 95%;
                padding: 10px; /* Decreased padding */
            }
            
            button {
                padding: 8px 12px; /* Decreased padding */
            }

            .task-item button {
                padding: 6px 10px; /* Decreased padding */
            }
        }
    </style>
</head>
<body>
    <div class="container">
        <h1>Task Manager</h1>
        <div>
            <label for="name">Name:</label>
            <input type="text" id="name" required>
        </div>
        <div>
            <label for="description">Description:</label>
            <textarea id="description" rows="4" required></textarea>
        </div>
        <div>
            <label for="due_date">Due Date:</label>
            <input type="date" id="due_date" required>
            <label for="due_time">Due Time:</label>
            <input type="time" id="due_time" required>
        </div>
        <div>
            <label for="reminder_date">Reminder Date:</label>
            <input type="date" id="reminder_date">
            <label for="reminder_time">Reminder Time:</label>
            <input type="time" id="reminder_time">
        </div>
        <button onclick="addTask()" id="addTaskBtn">Add Task</button>
        <h2>Tasks:</h2>
        <ul id="taskList"></ul>
    </div>

    <script>
        let tasks = [];

        function addTask() {
            const name = document.getElementById('name').value.trim();
            const description = document.getElementById('description').value.trim();
            const dueDate = document.getElementById('due_date').value;
            const dueTime = document.getElementById('due_time').value;
            const reminderDate = document.getElementById('reminder_date').value;
            const reminderTime = document.getElementById('reminder_time').value;

            if (!name || !description || !dueDate || !dueTime) {
                alert('Name, Description, Due Date, and Due Time are required.');
                return;
            }

            const task = {
                name: name,
                description: description,
                dueDate: dueDate + ' ' + dueTime,
                reminderDate: reminderDate,
                reminderTime: reminderTime,
                completed: false
            };

            tasks.push(task);
            displayTasks();
            setReminder(task);

            // Clear input fields
            document.getElementById('name').value = '';
            document.getElementById('description').value = '';
            document.getElementById('due_date').value = '';
            document.getElementById('due_time').value = '';
            document.getElementById('reminder_date').value = '';
            document.getElementById('reminder_time').value = '';

            // Disable add task button temporarily
            const addTaskBtn = document.getElementById('addTaskBtn');
            addTaskBtn.disabled = true;
            setTimeout(() => {
                addTaskBtn.disabled = false;
            }, 1000); // Re-enable after 1 second
        }

        function displayTasks() {
            const taskList = document.getElementById('taskList');
            taskList.innerHTML = '';

            tasks.forEach((task, index) => {
                const listItem = document.createElement('li');
                listItem.classList.add('task-item');
                listItem.innerHTML = `
                    <span class="task-details ${task.completed ? 'done' : ''}">
                        <strong>${task.name}</strong> - ${task.description} - Due: ${task.dueDate}
                    </span>
                    <button onclick="markAsDone(${index})">Mark as Done</button>
                `;
                taskList.appendChild(listItem);
            });
        }

        function setReminder(task) {
            const dueDateTime = new Date(task.dueDate);
            const reminderDateTime = task.reminderDate && task.reminderTime ? new Date(task.reminderDate + ' ' + task.reminderTime) : null;
            const now = new Date();

            if (reminderDateTime && dueDateTime > now && reminderDateTime > now && reminderDateTime < dueDateTime) {
                const timeDiff = reminderDateTime.getTime() - now.getTime();
                setTimeout(() => {
                    alert(`Reminder: Task "${task.name}" is due soon!`);
                }, timeDiff);
            }
        }

        function markAsDone(index) {
            tasks[index].completed = true;
            displayTasks();
        }
    </script>
</body>
</html>
