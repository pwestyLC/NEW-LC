using LcDevPack_TeamDamonA.Properties;
using MySqlConnector;
using System;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Windows.Forms;

namespace LcDevPack_TeamDamonA.Tools.MemoryWorker.OXRewards
{
    public class OXReward : Form
    {
        public static Connection connection = new Connection();
        private string Host = connection.Settings.SqlHost;
        private string User = connection.Settings.SqlUser;
        private string Password = connection.Settings.SqlPassword;
        private string Database = connection.Settings.SqlDatabase;
        private DatabaseHandle databaseHandle = new DatabaseHandle();

        private GroupBox groupBox4;
        private DataGridView dgItems;
        private GroupBox groupBox5;
        private Button button9;
        private PictureBox pictureBoxPreview;
        private TextBox textBoxQuizIndex;
        private TextBox[] itemIds = new TextBox[5];
        private TextBox[] itemCounts = new TextBox[5];
        private Label[] labelsId = new Label[5];
        private Label[] labelsCount = new Label[5];

        public OXReward()
        {
            InitializeComponent();
            FillGrid();
        }

        private void InitializeComponent()
        {
            this.Text = "O.X Reward Editor";
            this.ClientSize = new Size(900, 600);
            this.FormBorderStyle = FormBorderStyle.FixedSingle;
            this.MaximizeBox = false;

            // === Left side: data grid ===
            groupBox4 = new GroupBox
            {
                Text = "Reward Data",
                Location = new Point(10, 10),
                Size = new Size(500, 540)
            };

            dgItems = new DataGridView
            {
                Dock = DockStyle.Fill,
                AllowUserToAddRows = false,
                AllowUserToDeleteRows = false,
                ReadOnly = true,
                RowTemplate = { Height = 32 },
                SelectionMode = DataGridViewSelectionMode.FullRowSelect
            };

            dgItems.Columns.Add("Quiz", "Quiz");
            dgItems.Columns.Add(new DataGridViewImageColumn() { HeaderText = "Icon", Width = 32 });
            dgItems.Columns.Add("Item", "Item ID");
            dgItems.Columns.Add("ItemName", "Item Name");
            dgItems.Columns.Add("Count", "Count");

            dgItems.CellClick += dgItems_CellClick;
            groupBox4.Controls.Add(dgItems);

            // === Right side: editing ===
            groupBox5 = new GroupBox
            {
                Text = "Edit Rewards",
                Location = new Point(520, 10),
                Size = new Size(350, 400),
                Anchor = AnchorStyles.Top | AnchorStyles.Right
            };

            Label lblQuiz = new Label { Text = "Quiz Index:", Location = new Point(20, 30), AutoSize = true };
            textBoxQuizIndex = new TextBox { Location = new Point(100, 25), Width = 60, Enabled = false };
            groupBox5.Controls.Add(lblQuiz);
            groupBox5.Controls.Add(textBoxQuizIndex);

            // === Generate 5 pairs of item ID and count ===
            for (int i = 0; i < 5; i++)
            {
                int y = 60 + (i * 45);

                labelsId[i] = new Label
                {
                    Text = $"Item {i + 1} ID:",
                    Location = new Point(20, y + 3),
                    AutoSize = true
                };

                itemIds[i] = new TextBox
                {
                    Location = new Point(100, y),
                    Width = 80,
                    Tag = i
                };
                itemIds[i].TextChanged += ItemId_TextChanged;

                labelsCount[i] = new Label
                {
                    Text = "Count:",
                    Location = new Point(200, y + 3),
                    AutoSize = true
                };

                itemCounts[i] = new TextBox
                {
                    Location = new Point(250, y),
                    Width = 60
                };

                groupBox5.Controls.Add(labelsId[i]);
                groupBox5.Controls.Add(itemIds[i]);
                groupBox5.Controls.Add(labelsCount[i]);
                groupBox5.Controls.Add(itemCounts[i]);
            }

            // === Item preview icon ===
            pictureBoxPreview = new PictureBox
            {
                Location = new Point(150, 285),
                Size = new Size(48, 48),
                BorderStyle = BorderStyle.FixedSingle,
                SizeMode = PictureBoxSizeMode.StretchImage
            };
            groupBox5.Controls.Add(pictureBoxPreview);

            // === Save button ===
            button9 = new Button
            {
                Text = "Save Changes",
                Location = new Point(550, 450),
                Size = new Size(200, 40),
                Anchor = AnchorStyles.Bottom | AnchorStyles.Right
            };
            button9.Click += button9_Click;

            Controls.Add(groupBox4);
            Controls.Add(groupBox5);
            Controls.Add(button9);
        }

        private void ItemId_TextChanged(object sender, EventArgs e)
        {
            TextBox box = sender as TextBox;
            if (box == null || string.IsNullOrWhiteSpace(box.Text))
            {
                pictureBoxPreview.Image = null;
                return;
            }

            if (int.TryParse(box.Text, out int itemId))
            {
                pictureBoxPreview.Image = databaseHandle.IconFast(itemId);
            }
            else
            {
                pictureBoxPreview.Image = null;
            }
        }

        private void FillGrid()
        {
            dgItems.Rows.Clear();
            string query = "SELECT * FROM t_oxquiz_reward ORDER BY a_quiz_index";

            using (var conn = new MySqlConnection($"datasource={Host};Port=3306;User ID={User};Password={Password};Database={Database};Charset=utf8mb4;SslMode=Preferred;TlsVersion=Tls12;"))
            {
                conn.Open();
                using (var cmd = new MySqlCommand(query, conn))
                using (var reader = cmd.ExecuteReader())
                {
                    while (reader.Read())
                    {
                        int quizIndex = reader.GetInt32("a_quiz_index");

                        for (int i = 1; i <= 5; i++)
                        {
                            string itemCol = i == 1 ? "a_item_index" : $"a_item_index{i}";
                            string countCol = i == 1 ? "a_item_count" : $"a_item_count{i}";

                            int itemIdx = Convert.ToInt32(reader[itemCol]);
                            int count = Convert.ToInt32(reader[countCol]);

                            if (itemIdx <= 0)
                                continue;

                            Bitmap icon = databaseHandle.IconFast(itemIdx);
                            string name = databaseHandle.ItemNameFast(itemIdx);

                            dgItems.Rows.Add(quizIndex.ToString(), icon, itemIdx.ToString(), name, count.ToString());
                        }
                    }
                }
            }
        }

        private void dgItems_CellClick(object sender, DataGridViewCellEventArgs e)
        {
            if (e.RowIndex < 0)
                return;

            string quizIndex = dgItems.Rows[e.RowIndex].Cells["Quiz"].Value.ToString();
            textBoxQuizIndex.Text = quizIndex;

            using (var conn = new MySqlConnection($"datasource={Host};Port=3306;User ID={User};Password={Password};Database={Database};Charset=utf8mb4;SslMode=Preferred;TlsVersion=Tls12;"))
            {
                conn.Open();
                using (var cmd = new MySqlCommand($"SELECT * FROM t_oxquiz_reward WHERE a_quiz_index='{quizIndex}'", conn))
                using (var reader = cmd.ExecuteReader())
                {
                    if (reader.Read())
                    {
                        for (int i = 1; i <= 5; i++)
                        {
                            string itemCol = i == 1 ? "a_item_index" : $"a_item_index{i}";
                            string countCol = i == 1 ? "a_item_count" : $"a_item_count{i}";

                            itemIds[i - 1].Text = reader[itemCol].ToString();
                            itemCounts[i - 1].Text = reader[countCol].ToString();
                        }

                        // Show first item icon
                        if (int.TryParse(itemIds[0].Text, out int firstId))
                            pictureBoxPreview.Image = databaseHandle.IconFast(firstId);
                        else
                            pictureBoxPreview.Image = null;
                    }
                }
            }
        }

        private void button9_Click(object sender, EventArgs e)
        {
            if (string.IsNullOrEmpty(textBoxQuizIndex.Text))
            {
                MessageBox.Show("Select a quiz first.");
                return;
            }

            string query = $@"
                UPDATE {Database}.t_oxquiz_reward SET
                    a_item_index='{itemIds[0].Text}',
                    a_item_count='{itemCounts[0].Text}',
                    a_item_index2='{itemIds[1].Text}',
                    a_item_count2='{itemCounts[1].Text}',
                    a_item_index3='{itemIds[2].Text}',
                    a_item_count3='{itemCounts[2].Text}',
                    a_item_index4='{itemIds[3].Text}',
                    a_item_count4='{itemCounts[3].Text}',
                    a_item_index5='{itemIds[4].Text}',
                    a_item_count5='{itemCounts[4].Text}'
                WHERE a_quiz_index='{textBoxQuizIndex.Text}'";

            try
            {
                using (var conn = new MySqlConnection($"datasource={Host};Port=3306;User ID={User};Password={Password};Database={Database};Charset=utf8mb4;SslMode=Preferred;TlsVersion=Tls12;"))
                {
                    conn.Open();
                    MySqlCommand cmd = new MySqlCommand(query, conn);
                    cmd.ExecuteNonQuery();
                }

                MessageBox.Show("Rewards updated successfully!");
                FillGrid();
            }
            catch (Exception ex)
            {
                MessageBox.Show("Error saving rewards: " + ex.Message);
            }
        }
    }
}
