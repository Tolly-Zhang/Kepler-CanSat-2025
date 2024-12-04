import os
import subprocess

def is_ignored_by_git(path):
    """
    Check if the given path is ignored by git using `git check-ignore`.
    """
    try:
        result = subprocess.run(
            ["git", "check-ignore", "-q", path],
            cwd=os.path.dirname(path),
            stdout=subprocess.DEVNULL,
            stderr=subprocess.DEVNULL,
        )
        return result.returncode == 0
    except FileNotFoundError:
        print("Error: 'git' command not found. Ensure Git is installed and available in PATH.")
        return False

def manage_gitkeep(root_dir):
    """
    Add or remove .gitkeep files in empty directories,
    skipping those ignored by .gitignore.
    """
    for dirpath, dirnames, filenames in os.walk(root_dir):
        # Remove hidden directories
        dirnames[:] = [d for d in dirnames if not d.startswith('.')]
        
        # Skip processing if the directory is ignored by git
        if is_ignored_by_git(dirpath):
            continue

        gitkeep_path = os.path.join(dirpath, ".gitkeep")
        files_without_gitkeep = [f for f in filenames if f != '.gitkeep']

        if not files_without_gitkeep:
            # Add .gitkeep if directory is empty
            if not os.path.exists(gitkeep_path):
                with open(gitkeep_path, 'w') as f:
                    f.write("")
                print(f"Added .gitkeep to: {dirpath}")
        else:
            # Remove .gitkeep if directory is no longer empty
            if os.path.exists(gitkeep_path):
                os.remove(gitkeep_path)
                print(f"Removed .gitkeep from: {dirpath}")

# Update the path to your repository
repo_path = r'F:\CanSat\Kepler-CanSat-2025'
manage_gitkeep(repo_path)
